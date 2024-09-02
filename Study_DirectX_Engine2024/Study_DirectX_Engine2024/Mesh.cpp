#include "Mesh.h"


Mesh::Mesh(const Description& desc)
	: m_pVtxBuffer(NULL), m_pIdxBuffer(NULL), m_desc{}
{
	HRESULT hr = E_FAIL;
	hr = CreateVertexBuffer(desc.pVtx, desc.vtxSize, desc.vtxCount, desc.isWrite);
	if (desc.pIdx)
	{
		hr = CreateIndexBuffer(desc.pIdx, desc.idxSize, desc.idxCount);
	}
	m_desc = desc;

	rsize_t vtxMemSize = desc.vtxSize * desc.vtxCount;
	void* pVtx = new char[vtxMemSize];
	memcpy_s(pVtx, vtxMemSize, desc.pVtx, vtxMemSize);
	m_desc.pVtx = pVtx;
	rsize_t idxMemSize = desc.idxSize * desc.idxCount;
	void* pIdx = new char[idxMemSize];
	memcpy_s(pIdx, idxMemSize, desc.pIdx, idxMemSize);
	m_desc.pIdx = pIdx;

}

Mesh::~Mesh()
{
	delete[] m_desc.pIdx;
	delete[] m_desc.pVtx;
	SAFE_RELEASE(m_pIdxBuffer);
	SAFE_RELEASE(m_pVtxBuffer);
}

HRESULT Mesh::CreateVertexBuffer(const void* pVtx, UINT size, UINT count, bool isWrite)
{
	//--- �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- �o�b�t�@�̏����l��ݒ�
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pVtx;

	//--- ���_�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device* pDevice = DirectXManager::GetInstance().GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuffer);

	return hr;
}

HRESULT Mesh::CreateIndexBuffer(const void* pIdx, UINT size, UINT count)
{
	// �C���f�b�N�X�T�C�Y�̊m�F
	switch (size)
	{
	default:
		return E_FAIL;
	case 2:
	case 4:
		break;
	}

	// �o�b�t�@�̏���ݒ�
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// �o�b�t�@�̏����f�[�^
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	// �C���f�b�N�X�o�b�t�@����
	ID3D11Device* pDevice = DirectXManager::GetInstance().GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIdxBuffer);

	return hr;
}

void Mesh::Draw(int count)
{
	ID3D11DeviceContext* pContext = DirectXManager::GetInstance().GetContext();
	UINT stride = m_desc.vtxSize;
	UINT offset = 0;

	// �g�|���W�̐ݒ�
	ID3D11HullShader* hullShader;
	pContext->HSGetShader(&hullShader, nullptr, nullptr);
	if (hullShader)
		hullShader->Release();
	else
		pContext->IASetPrimitiveTopology(m_desc.topology);

	// ���_�o�b�t�@�ݒ�
	pContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &stride, &offset);

	// �`��
	if (m_desc.idxCount > 0)
	{
		DXGI_FORMAT format;
		switch (m_desc.idxSize)
		{
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		}
		pContext->IASetIndexBuffer(m_pIdxBuffer, format, 0);
		pContext->DrawIndexed(count ? count : m_desc.idxCount, 0, 0);
	}
	else
	{
		// ���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(count ? count : m_desc.vtxCount, 0);
	}

}

HRESULT Mesh::Write(void* pVtx)
{
	if (!m_desc.isWrite) { return E_FAIL; }

	HRESULT hr;
	ID3D11Device* pDevice = DirectXManager::GetInstance().GetDevice();
	ID3D11DeviceContext* pContext = DirectXManager::GetInstance().GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;

	// �f�[�^�R�s�[
	hr = pContext->Map(m_pVtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (SUCCEEDED(hr))
	{
		rsize_t size = m_desc.vtxCount * m_desc.vtxSize;
		memcpy_s(mapResource.pData, size, pVtx, size);
		pContext->Unmap(m_pVtxBuffer, 0);
	}
	return hr;
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{
	return m_pVtxBuffer;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	return m_pIdxBuffer;
}

Mesh::Description Mesh::GetDesc()
{
	return m_desc;
}