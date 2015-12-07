#include "DirectXRenderer.h"
#include "PAssert.h"
#include "DirectXShader.h"
using namespace RenderCore;

DirectXRenderer::DirectXRenderer(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
: Renderer(instance, windowClass, windowTitle, showCommand),
mFeatureLevel(D3D_FEATURE_LEVEL_9_1),
mDirect3DDevice(nullptr),
mDirect3DDeviceContext(nullptr),
mSwapChain(nullptr),
mDepthStencilBuffer(nullptr),
mRenderTargertView(nullptr),
mDepthStencilView(nullptr),
mViewport(),
mFrameRate(60),
mMultiSamplingQualityLevels(0),
mMultiSamplingCount(4),
mDepthStencilBufferEnabled(true),
mMultiSamplingEnabled(true),
mBackGroundColor(0.392f, 0.584f, 0.929f, 1.0f),
camera(PerspectiveCamera::DefaultFieldOfView, 0, PerspectiveCamera::DefaultNearPlaneDistance, PerspectiveCamera::DefaultFarPlaneDistance)
{
	
}

DirectXRenderer::~DirectXRenderer()
{
	Shutdown();
}

void DirectXRenderer::Initialize()
{
	Renderer::Initialize();
	InitializeDirectX();
	camera.Reset();
	camera.SetAspectRatio((float)mScreenWidth/(float)mScreeHeight);
	camera.Initialize();
	camera.SetPosition(0.0f, 0, -10.0f);
}

void DirectXRenderer::Shutdown()
{
	RELEASEOBJECT(mRenderTargertView);
	RELEASEOBJECT(mDepthStencilView);
	RELEASEOBJECT(mSwapChain);
	RELEASEOBJECT(mDepthStencilBuffer);

	if (mDirect3DDeviceContext != nullptr)
	{
		mDirect3DDeviceContext->ClearState();
	}

	RELEASEOBJECT(mDirect3DDeviceContext);
	RELEASEOBJECT(mDirect3DDevice);
}

void DirectXRenderer::InitializeDirectX()
{
	HRESULT hr;
	unsigned int createDeviceFlags = 0;

#if defined (DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	// Create the Direct3D device and device context
	D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &mDirect3DDevice, &mFeatureLevel, &mDirect3DDeviceContext);
	ASSERT(NULL != mDirect3DDevice, "Error creating D3D device");
	ASSERT(mDirect3DDeviceContext != NULL, "Error creating D3D device context");

	// Check for multi sampling support
	mDirect3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, mMultiSamplingCount, &mMultiSamplingQualityLevels);
	if (mMultiSamplingQualityLevels == 0)
	{
		//TODO: some code informing that multi sampling is unsupported.
	}

	DXGI_SWAP_CHAIN_DESC1 swapCahinDesc;
	ZeroMemory(&swapCahinDesc, sizeof(swapCahinDesc));
	swapCahinDesc.Width = mScreenWidth;
	swapCahinDesc.Height = mScreeHeight;
	swapCahinDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (mMultiSamplingEnabled)
	{
		swapCahinDesc.SampleDesc.Count = mMultiSamplingCount;
		swapCahinDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
	}
	else
	{
		swapCahinDesc.SampleDesc.Count = 1;
		swapCahinDesc.SampleDesc.Quality = 0;
	}

	swapCahinDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapCahinDesc.BufferCount = 1;
	swapCahinDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Create the swap chain.
	IDXGIDevice* dxgiDevice = nullptr;
	mDirect3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	ASSERT(dxgiDevice != NULL, "Error Creating dxgiDevice");

	IDXGIAdapter* dxgiAdapter = nullptr;
	if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter))))
	{
		//TODO: some kind of error checking htat queryinterface failed
		RELEASEOBJECT(dxgiDevice);
	}

	IDXGIFactory2* dxgiFactory = nullptr;
	if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory))))
	{
		//TODO: some kind of error checking that queryinteface failed.
		RELEASEOBJECT(dxgiDevice);
		RELEASEOBJECT(dxgiAdapter);
	}

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
	ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
	fullScreenDesc.RefreshRate.Numerator = mFrameRate;
	fullScreenDesc.RefreshRate.Denominator = 1;
	fullScreenDesc.Windowed = !mIsFullScreen;

	if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, mWindow->GetWindowHandle(), &swapCahinDesc, &fullScreenDesc, nullptr, &mSwapChain)))
	{
		//TODO: somne sort of error code signifying that CreateSwapCahinForHwnd failed
		RELEASEOBJECT(dxgiDevice);
		RELEASEOBJECT(dxgiAdapter);
		RELEASEOBJECT(dxgiFactory);
	}

	RELEASEOBJECT(dxgiDevice);
	RELEASEOBJECT(dxgiAdapter);
	RELEASEOBJECT(dxgiFactory);

	// Create the render target view
	ID3D11Texture2D* backBuffer;
	if (FAILED(hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
	{
		//TODO: Some error code for GetBuffer

	}

	backBuffer->GetDesc(&mBackBufferDesc);

	if (FAILED(hr = mDirect3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargertView)))
	{
		//TODO: Some error code for CreateRenderTargetView
		RELEASEOBJECT(backBuffer);
	}

	RELEASEOBJECT(backBuffer);

	// Create the depth stencil view
	if (mDepthStencilBufferEnabled)
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = mScreenWidth;
		depthStencilDesc.Height = mScreeHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

		if (mMultiSamplingEnabled)
		{
			depthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
			depthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}

		if (FAILED(hr = mDirect3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
		{
			//TODO: Error for CreateTexture2D depthstencil
		}

		if (FAILED(hr = mDirect3DDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView)))
		{
			//TODO: Error for CreateDepthStencilView
		}
	}

	// Bind the render target and depth-stencil views to OM stage
	mDirect3DDeviceContext->OMSetRenderTargets(1, &mRenderTargertView, mDepthStencilView);

	mViewport.TopLeftX = mViewport.TopLeftY = 0.0f;
	mViewport.Width = static_cast<float>(mScreenWidth);
	mViewport.Height = static_cast<float>(mScreeHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;

	// Set the viewport
	mDirect3DDeviceContext->RSSetViewports(1, &mViewport);

}

void DirectXRenderer::Update(const Core::GameTime& gameTime)
{
	camera.Update(gameTime);
}

void DirectXRenderer::Draw(const Core::GameTime& gameTime)
{
	mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargertView, reinterpret_cast<const float*>(mBackGroundColor.data));
	mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render all the active/visible render components. 
	// Components are currently batched by material. This assumes every model uses one material (this assumption will be worked on later to allow multi material models)
	// Materials are batched by the shader they use. All of this reduces the amount of render state that needs to change between draw calls.
	for (std::map<std::string, DirectXShader*>::iterator sIt = mShaderTable.begin(); sIt != mShaderTable.end(); ++sIt)
	{
		// Set the active shader
		DirectXShader* shader = sIt->second;
		shader->SetActiveShader(mDirect3DDeviceContext);
		shader->SetPerFrameBuffer(mDirect3DDeviceContext, &camera);

		std::vector<Material*>& materials = mShaderIndexToMaterialMap[sIt->second->ShaderName()];
		for (std::vector<Material*>::iterator mIt = materials.begin(); mIt != materials.end(); ++mIt)
		{
			// Do material stuff
			std::vector<Renderable*>& renderables = mMaterialIndexToRenderableMap[(*mIt)->MaterialName()];
			for (std::vector<Renderable*>::iterator rIt = renderables.begin(); rIt != renderables.end(); ++rIt)
			{
				shader->SetPerInstanceBuffer(mDirect3DDeviceContext, *rIt);
				
				const std::vector<Mesh*>& meshes = (*rIt)->GetModel()->GetMeshes();

				for (std::vector<Mesh*>::const_iterator it = meshes.begin(); it != meshes.end(); ++it)
				{
					Mesh* mesh = (*it);

					unsigned int stride = mesh->VertexSize();
					unsigned int offset = 0;

					ID3D11Buffer* vBuffer = mesh->GetVertexBuffer();
					ID3D11Buffer* iBuffer = mesh->GetIndexBuffer();

					mDirect3DDeviceContext->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
					mDirect3DDeviceContext->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);
					mDirect3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

					mDirect3DDeviceContext->DrawIndexed(mesh->NumIndices(), 0, 0);
				}
			}
		}
	}

	mSwapChain->Present(0, 0);
}

ID3D11Device* DirectXRenderer::Direct3DDevice() const
{
	return mDirect3DDevice;
}

ID3D11DeviceContext* DirectXRenderer::Direct3DDeviceContext() const
{
	return mDirect3DDeviceContext;
}