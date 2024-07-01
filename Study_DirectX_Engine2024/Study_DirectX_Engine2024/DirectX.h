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
	// DirectX初期化処理
	HRESULT InitDirectX(HWND _hWnd, int _height, int _width);

	// 終了処理
	void UninitDirectX();
	// スワップチェイン処理
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
	// メンバー変数
	ID3D11Device*				m_pDevice;										// デバイス
	ID3D11DeviceContext*		m_pContext;										// デバイスコンテキスト
	IDXGISwapChain*				m_pSwapChain;									// スワップチェイン
	ID3D11RasterizerState*		m_pRasterizerState[3];							// ラスタライザ
	ID3D11BlendState*			m_pBlendState[BlendMode::BLEND_MAX];			// ブレンドステート
	ID3D11SamplerState*			m_pSamplerState[SamplerState::SAMPLER_MAX];		// サンプラー
	ID3D11DepthStencilState*	m_pDepthStencilState[DepthState::DEPTH_MAX];	// ステンシル

	// 自身の変数を持たせておく
	static DirectX m_Instance;

private :
	DirectX(){}
	~DirectX(){}
};

