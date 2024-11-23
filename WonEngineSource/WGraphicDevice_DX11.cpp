#include "WGraphicDevice_DX11.h"
#include "WonApplication.h"

extern Won::WonApplication application;

namespace Won 
{
	WGraphicDevice_DX11::WGraphicDevice_DX11()
	{

	}
	WGraphicDevice_DX11::~WGraphicDevice_DX11()
	{

	}

	void WGraphicDevice_DX11::Initialize() 
	{
		D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationflags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		HRESULT result = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, creationflags, featurelevels,
			ARRAYSIZE(featurelevels), D3D11_SDK_VERSION, mDevice.GetAddressOf(), 0, mDeviceContext.GetAddressOf());

		DXGI_SWAP_CHAIN_DESC swapchaindesc = {};

		swapchaindesc.BufferCount = 2;
		swapchaindesc.Windowed = true;
		swapchaindesc.OutputWindow = application.GetEngineWND();
		swapchaindesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		swapchaindesc.BufferDesc.Width = application.GetWidth();
		swapchaindesc.BufferDesc.Height = application.GetHeight();
		swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapchaindesc.BufferDesc.RefreshRate.Numerator = 60;
		swapchaindesc.BufferDesc.RefreshRate.Denominator = 1;

		swapchaindesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapchaindesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		UINT quility = 0;
		mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &quility);

		swapchaindesc.SampleDesc.Count = 1;
		swapchaindesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> mDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> mAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> mFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)mDXGIDevice.GetAddressOf())))
			return;

		if (FAILED(mDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)mAdapter.GetAddressOf())))
			return;

		if (FAILED(mAdapter->GetParent(__uuidof(IDXGIFactory), (void**)mFactory.GetAddressOf())))
			return;

		if (FAILED(mFactory->CreateSwapChain(mDevice.Get(), &swapchaindesc, mSwapChain.GetAddressOf())))
			return;



	}

	void WGraphicDevice_DX11::Render() 
	{

	}

}