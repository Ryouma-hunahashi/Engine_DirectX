#include "GeometryDrawer.h"

GeometryDrawer::InternalData GeometryDrawer::m_data;


void GeometryDrawer::Init()
{
	for (int i = 0; i < 3; ++i)
		DirectX::XMStoreFloat4x4(&m_data.matrices[i], DirectX::XMMatrixIdentity());
	m_data.parameters[0] = DirectX::XMFLOAT4(1, 1, 1, 1);
	m_data.parameters[1] = DirectX::XMFLOAT4(1, 1, 1, 1);

	CreateVertexShader();
	CreatePixelShader();
	CreateLineMesh();
	CreateBoxMesh();
	CreateSphereMesh();
}
void GeometryDrawer::Uninit()
{
	m_data.sphereMesh.reset();
	m_data.boxMesh.reset();
	m_data.lineMesh.reset();
	m_data.defaultVS.reset();
	m_data.defaultPS.reset();
}

void GeometryDrawer::SetVertexShader(VertexShader* _vs)
{
	m_data.currentVS = _vs;
}
void GeometryDrawer::SetPixelShader(PixelShader* _ps)
{
	m_data.currentPS = _ps;
}
void GeometryDrawer::SetWorld(DirectX::XMFLOAT4X4 _world)
{
	m_data.matrices[0] = _world;
}
void GeometryDrawer::SetView(DirectX::XMFLOAT4X4 _view)
{
	m_data.matrices[1] = _view;
}
void GeometryDrawer::SetProjection(DirectX::XMFLOAT4X4 _proj)
{
	m_data.matrices[2] = _proj;
}
void GeometryDrawer::SetColor(DirectX::XMFLOAT4 _color)
{
	m_data.parameters[0] = _color;
}
void GeometryDrawer::SetLightDirection(DirectX::XMFLOAT3 _dir)
{
	DirectX::XMVECTOR vDir = DirectX::XMLoadFloat3(&_dir);
	DirectX::XMStoreFloat3(&_dir, DirectX::XMVector3Normalize(vDir));
	m_data.parameters[1].x = _dir.x;
	m_data.parameters[1].y = _dir.y;
	m_data.parameters[1].z = _dir.z;
}
void GeometryDrawer::EnableLight(bool _enable)
{
	m_data.parameters[1].w = _enable ? 0.0f : 1.0f;
}

void GeometryDrawer::AddLine(const DirectX::XMFLOAT3 _start, const DirectX::XMFLOAT3 _end)
{
	if (m_data.lineCount < InternalData::MAX_LINES)
	{
		m_data.lineVertices[m_data.lineCount].position = _start;
		m_data.lineVertices[m_data.lineCount].color = m_data.parameters[0];
		++m_data.lineCount;
		m_data.lineVertices[m_data.lineCount].position = _end;
		m_data.lineVertices[m_data.lineCount].color = m_data.parameters[0];
		++m_data.lineCount;
	}
}
void GeometryDrawer::AddLine(
	DirectX::XMFLOAT3 _startPos, DirectX::XMFLOAT4 _startColor,
	DirectX::XMFLOAT3 _endPos, DirectX::XMFLOAT4 _endColor)
{
	if (m_data.lineCount < InternalData::MAX_LINES)
	{
		m_data.lineVertices[m_data.lineCount].position = _startPos;
		m_data.lineVertices[m_data.lineCount].color = _startColor;
		++m_data.lineCount;
		m_data.lineVertices[m_data.lineCount].position = _endPos;
		m_data.lineVertices[m_data.lineCount].color = _endColor;
		++m_data.lineCount;
	}
}
void GeometryDrawer::DrawLines()
{
	DirectX::XMFLOAT4X4 worldBackup = m_data.matrices[0];
	DirectX::XMFLOAT4 colorBackup = m_data.parameters[0];
	float lightBackup = m_data.parameters[1].w;

	DirectX::XMStoreFloat4x4(&m_data.matrices[0], DirectX::XMMatrixIdentity());
	m_data.parameters[0] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_data.parameters[1].w = 1.0f;

	m_data.currentVS->WriteBuffer(0, m_data.matrices);
	m_data.currentVS->WriteBuffer(1, m_data.parameters);
	m_data.currentVS->Bind();
	m_data.currentPS->Bind();
	m_data.lineMesh->Write(m_data.lineVertices);
	m_data.lineMesh->Draw(m_data.lineCount);

	m_data.matrices[0] = worldBackup;
	m_data.parameters[0] = colorBackup;
	m_data.parameters[1].w = lightBackup;

	m_data.lineCount = 0;
}
void GeometryDrawer::DrawBox()
{
	m_data.currentVS->WriteBuffer(0, m_data.matrices);
	m_data.currentVS->WriteBuffer(1, m_data.parameters);
	m_data.currentVS->Bind();
	m_data.currentPS->Bind();
	m_data.boxMesh->Draw();
}
void GeometryDrawer::DrawSphere()
{
	m_data.currentVS->WriteBuffer(0, m_data.matrices);
	m_data.currentVS->WriteBuffer(1, m_data.parameters);
	m_data.currentVS->Bind();
	m_data.currentPS->Bind();
	m_data.sphereMesh->Draw();
}

void GeometryDrawer::CreateVertexShader()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float4 color : COLOR0;
	float3 normal : NORMAL0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float4 color;
	float4 light;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	
	float3 N = normalize(mul(vin.normal, (float3x3)world));
	float3 L = normalize(light.xyz);
	float diffuse = dot(N, L) * 0.5f + 0.5f;
	diffuse = saturate(diffuse + light.w);
	vout.color = vin.color * color * diffuse;

	return vout;
})EOT";
	m_data.defaultVS = std::make_shared<VertexShader>();
	HRESULT hr = m_data.defaultVS->Compile(VSCode);
	m_data.currentVS = m_data.defaultVS.get();
}

void GeometryDrawer::CreatePixelShader()
{
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
})EOT";
	m_data.defaultPS = std::make_shared<PixelShader>();
	HRESULT hr = m_data.defaultPS->Compile(PSCode);
	m_data.currentPS = m_data.defaultPS.get();
}

void GeometryDrawer::CreateLineMesh()
{
	Mesh::Description desc = {};
	for (int i = 0; i < InternalData::MAX_LINES; ++i)
	{
		m_data.lineVertices[i].position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_data.lineVertices[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_data.lineVertices[i].normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	desc.pVtx = m_data.lineVertices;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = InternalData::MAX_LINES;
	desc.isWrite = true;
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	m_data.lineCount = 0;
	m_data.lineMesh = std::make_shared<Mesh>(desc);
}
void GeometryDrawer::CreateBoxMesh()
{
	const float d = 0.5f;
	DirectX::XMFLOAT4 color(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMFLOAT3 normal[] = {
		DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f,-1.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f,-1.0f),
	};
	Vertex vtx[] = {
		// +X
		{DirectX::XMFLOAT3(d, d,-d), color, normal[0]},
		{DirectX::XMFLOAT3(d, d, d), color, normal[0]},
		{DirectX::XMFLOAT3(d,-d,-d), color, normal[0]},
		{DirectX::XMFLOAT3(d,-d, d), color, normal[0]},
		// -X
		{DirectX::XMFLOAT3(-d, d, d), color, normal[1]},
		{DirectX::XMFLOAT3(-d, d,-d), color, normal[1]},
		{DirectX::XMFLOAT3(-d,-d, d), color, normal[1]},
		{DirectX::XMFLOAT3(-d,-d,-d), color, normal[1]},
		// +Y
		{DirectX::XMFLOAT3(-d, d, d), color, normal[2]},
		{DirectX::XMFLOAT3(d, d, d), color, normal[2]},
		{DirectX::XMFLOAT3(-d, d,-d), color, normal[2]},
		{DirectX::XMFLOAT3(d, d,-d), color, normal[2]},
		// -Y
		{DirectX::XMFLOAT3(-d,-d,-d), color, normal[3]},
		{DirectX::XMFLOAT3(d,-d,-d), color, normal[3]},
		{DirectX::XMFLOAT3(-d,-d, d), color, normal[3]},
		{DirectX::XMFLOAT3(d,-d, d), color, normal[3]},
		// +Z
		{DirectX::XMFLOAT3(-d, d, d), color, normal[4]},
		{DirectX::XMFLOAT3(d, d, d), color, normal[4]},
		{DirectX::XMFLOAT3(-d,-d, d), color, normal[4]},
		{DirectX::XMFLOAT3(d,-d, d), color, normal[4]},
		// -Z
		{DirectX::XMFLOAT3(-d,-d,-d), color, normal[5]},
		{DirectX::XMFLOAT3(d,-d,-d), color, normal[5]},
		{DirectX::XMFLOAT3(-d, d,-d), color, normal[5]},
		{DirectX::XMFLOAT3(d, d,-d), color, normal[5]},
	};
	WORD idx[] = {
		 2, 0, 1,  1, 3, 2,
		 6, 4, 5,  5, 7, 6,
		10, 8, 9,  9,11,10,
		14,12,13, 13,15,14,
		18,16,17, 17,19,18,
		22,20,21, 21,23,22,
	};
	Mesh::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.pIdx = idx;
	desc.idxSize = sizeof(idx[0]);
	desc.idxCount = _countof(idx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_data.boxMesh = std::make_shared<Mesh>(desc);
}
void GeometryDrawer::CreateSphereMesh()
{
	std::vector<Vertex> vtx;
	const int detail = 32;
	for (int j = 0; j < detail / 2 + 1; ++j)
	{
		float radY = DirectX::XM_2PI / detail * j;
		for (int i = 0; i < detail; ++i)
		{
			float radXZ = DirectX::XM_2PI / detail * i;
			float x = sinf(radY) * sinf(radXZ);
			float y = cosf(radY);
			float z = sinf(radY) * cosf(radXZ);
			vtx.push_back({
				DirectX::XMFLOAT3(x * 0.5f, y * 0.5f, z * 0.5f),
				DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
				DirectX::XMFLOAT3(x, y, z)
				});
		}
	}
	std::vector<DWORD> idx;
	for (int j = 0; j < detail / 2; ++j)
	{
		for (int i = 0; i < detail; ++i)
		{
			idx.push_back((j + 1) * detail + i);
			idx.push_back(j * detail + i);
			idx.push_back(j * detail + ((i + 1) % detail));
			idx.push_back(idx.back());
			idx.push_back((j + 1) * detail + ((i + 1) % detail));
			idx.push_back((j + 1) * detail + i);
		}
	}
	Mesh::Description desc = {};
	desc.pVtx = vtx.data();
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = static_cast<UINT>(vtx.size());
	desc.pIdx = idx.data();
	desc.idxSize = sizeof(idx[0]);
	desc.idxCount = static_cast<UINT>(idx.size());
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_data.sphereMesh = std::make_shared<Mesh>(desc);
}