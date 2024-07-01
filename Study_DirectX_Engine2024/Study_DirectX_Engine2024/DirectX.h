#pragma once

#pragma region includes
#include <d3d11.h>
#pragma endregion

#pragma region library
#pragma comment (lib,"d3d11.lib")
#pragma endregion

#define SAFE_RELEASE(p) do{if(p){p->Release(); p = nullptr;}}

enum BlendMode
{
	BLEND_NONE,
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_ADDALPHA,
	BLEND_SUB,
	BLEND_SCREEN,
	BLEND_MAX
};

enum SamplerState
{
	SAMPLER_LINEAR,
	SAMPLER_POINT,
	SAMPLER_MAX
};

enum DepthState
{
	DEPTH_ENABLE_WRITE_TEST,
	DEPTH_ENABLE_TEST,
	DEPTH_DISABLE,
	DEPTH_MAX
};

class DirectX
{
public:
	// DirectX����������
	HRESULT InitDirectX(HWND _hWnd, int _height, int _width);

	// �I������
	void UninitDirectX();
	// �X���b�v�`�F�C������
	void SwapDirectX();

#pragma region Setter
	//void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);
	void SetCullingMode(D3D11_CULL_MODE cull);
	void SetDepthTest(DepthState state);
	void SetBlendMode(BlendMode blend);
	void SetSamplerState(SamplerState state);
#pragma endregion

#pragma region Getter
	ID3D11Device* GetDevice()			{ return m_pDevice; }
	ID3D11DeviceContext* GetContext()	{ return m_pContext; }
	IDXGISwapChain* GetSwapChain()		{ return m_pSwapChain; }
	static DirectX& GetInstance()		{ return m_Instance; }
#pragma endregion

private:
	// �����o�[�ϐ�
	ID3D11Device*				m_pDevice;										// �f�o�C�X
	ID3D11DeviceContext*		m_pContext;										// �f�o�C�X�R���e�L�X�g
	IDXGISwapChain*				m_pSwapChain;									// �X���b�v�`�F�C��
	ID3D11RasterizerState*		m_pRasterizerState[3];							// ���X�^���C�U
	ID3D11BlendState*			m_pBlendState[BlendMode::BLEND_MAX];			// �u�����h�X�e�[�g
	ID3D11SamplerState*			m_pSamplerState[SamplerState::SAMPLER_MAX];		// �T���v���[
	ID3D11DepthStencilState*	m_pDepthStencilState[DepthState::DEPTH_MAX];	// �X�e���V��

	// ���g�̕ϐ����������Ă���
	static DirectX m_Instance;

private :
	DirectX(){}
	~DirectX(){}
};

