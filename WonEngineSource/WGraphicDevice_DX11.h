#pragma once

#include "includeHeader.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Won
{
	class WGraphicDevice_DX11
	{
	public:
		WGraphicDevice_DX11();
		~WGraphicDevice_DX11();

		void Initialize();
		void Render();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> mSamplers;


	};
}

