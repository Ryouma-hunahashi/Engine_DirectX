#pragma once

#include "DirectX.h"

class Mesh
{
public:
	struct Description
	{
		const void* pVtx;
		UINT vtxSize;
		UINT vtxCount;
		bool isWrite;
		const void* pIdx;
		UINT idxSize;
		UINT idxCount;
		D3D11_PRIMITIVE_TOPOLOGY topology;
	};
public:
	Mesh(const Description& desc);
	~Mesh();

	void Draw(int count = 0);
	HRESULT Write(void* pVtx);
	Description GetDesc();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

private:
	HRESULT CreateVertexBuffer(const void* pIdx, UINT size, UINT count, bool isWrite);
	HRESULT CreateIndexBuffer(const void* pVtx, UINT size, UINT count);

private:

	ID3D11Buffer* m_pVtxBuffer;
	ID3D11Buffer* m_pIdxBuffer;
	Description m_desc;

};
