#pragma once
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <d3d10.h>
#include <d3dx10.h>
#include <DXGI.h>  // Thêm thư viện DXGI cho swap chain
#include "GameDefines.h"

class CGraphics
{
private:
    ID3D10Device* pDevice;            
    IDXGISwapChain* pSwapChain;         
    ID3D10RenderTargetView* pRenderTargetView; // Render target view

    D3D10_DRIVER_TYPE driverType;      
    DXGI_SWAP_CHAIN_DESC swapChainDesc; 

    HRESULT result;
    HWND hWnd;
    bool fullscreen;
    int width;
    int height;

    float clearColor[4];               


    bool InitDirect3DAndSwapChain();

public:
    CGraphics();
    ~CGraphics();


    bool Initialize(HWND hw);


    void Clear();
    void BeginScene();  
    void EndScene();    
    void Present();


    ID3D10Device* GetDevice() { return pDevice; }


    void SetClearColor(float r, float g, float b, float a = 1.0f) {
        clearColor[0] = r;
        clearColor[1] = g;
        clearColor[2] = b;
        clearColor[3] = a;
    }
};

#endif