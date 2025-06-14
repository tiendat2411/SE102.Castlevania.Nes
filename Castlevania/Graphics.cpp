#include "Graphics.h"

// Constructor
CGraphics::CGraphics() :
    pDevice(nullptr),
    pSwapChain(nullptr),
    pRenderTargetView(nullptr),
    driverType(D3D10_DRIVER_TYPE_NULL),
    hWnd(nullptr),
    fullscreen(FULLSCREEN),
    width(GAME_WIDTH),
    height(GAME_HEIGHT)
{
    // Màu clear mặc định (đen)
    clearColor[0] = 0.0f;
    clearColor[1] = 0.0f;
    clearColor[2] = 0.0f;
    clearColor[3] = 1.0f;
}

// Destructor
CGraphics::~CGraphics()
{
    // Giải phóng các tài nguyên DirectX theo thứ tự ngược với khởi tạo
    if (pRenderTargetView) pRenderTargetView->Release();
    if (pSwapChain) pSwapChain->Release();
    if (pDevice) pDevice->Release();
}

// Khởi tạo đồ họa DirectX 10
bool CGraphics::Initialize(HWND hw)
{
    hWnd = hw;

    // Lấy kích thước client area thực tế
    RECT rc;
    GetClientRect(hWnd, &rc);
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;

    return InitDirect3DAndSwapChain();
}

// Khởi tạo device và swap chain
bool CGraphics::InitDirect3DAndSwapChain()
{
    HRESULT hr = S_OK;

    // Thiết lập swap chain description
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = !fullscreen;

    // Cờ tạo device (thêm debug layer nếu ở chế độ debug)
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    // Thử tạo device với hardware acceleration trước
    driverType = D3D10_DRIVER_TYPE_HARDWARE;
    hr = D3D10CreateDeviceAndSwapChain(
        nullptr,                        // Adapter mặc định
        driverType,                     // Driver type
        nullptr,                        // Software rasterizer (không dùng)
        createDeviceFlags,               // Cờ tạo device
        D3D10_SDK_VERSION,              // SDK version
        &swapChainDesc,                 // Swap chain description
        &pSwapChain,                    // Con trỏ swap chain
        &pDevice                       // Con trỏ device
    );

    if (FAILED(hr))
    {
        driverType = D3D10_DRIVER_TYPE_WARP;
        hr = D3D10CreateDeviceAndSwapChain(
            nullptr, driverType, nullptr, createDeviceFlags,
            D3D10_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice);

        if (FAILED(hr))
        {
            MessageBox(hWnd, TEXT("Failed to create Direct3D 10 device"), TEXT("Error"), MB_OK);
            return false;
        }
    }

    ID3D10Texture2D* pBackBuffer = nullptr;
    hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("Failed to get swap chain back buffer"), TEXT("Error"), MB_OK);
        return false;
    }

    hr = pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        MessageBox(hWnd, TEXT("Failed to create render target view"), TEXT("Error"), MB_OK);
        return false;
    }

    pDevice->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

    D3D10_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pDevice->RSSetViewports(1, &vp);

    return true;
}

void CGraphics::Clear()
{
    pDevice->ClearRenderTargetView(pRenderTargetView, clearColor);
}

void CGraphics::BeginScene()
{
    Clear();
}

void CGraphics::EndScene()
{

}

void CGraphics::Present()
{
    pSwapChain->Present(0, 0);
}