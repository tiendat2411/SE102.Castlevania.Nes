/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"

#include "Simon.h"
//#include "Mario.h"
#include "Brick.h"

#include "SampleKeyEventHandler.h"
#include "Sprites.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"03 - Keyboard and Mario states"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_SIMON1 0
#define ID_TEX_SIMON2 1
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

#define ID_SPRITE_BRICK 20001

#define TEXTURES_DIR L"textures"
//#define texture_path_mario textures_dir "\\mario1.png"
#define TEXTURE_PATH_SIMON1 TEXTURES_DIR "\\simon1.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\2.png"

#define SIMON_START_X 200.0f
#define SIMON_START_Y 10.0f

//#define BRICK_X 0.0f
//#define BRICK_Y GROUND_Y + 31.0f
//#define NUM_BRICKS 50

#define BRICK_X 0.0f
#define BRICK_Y /*GROUND_Y* +*/ 20.0f
#define NUM_BRICKS 50

CSimon* simon = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and simon object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON1, TEXTURE_PATH_SIMON1,8,3,24);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	LPTEXTURE texSimon1 = textures->Get(ID_TEX_SIMON1);
	LPTEXTURE texSimon2 = textures->Get(ID_TEX_SIMON2);

	sprites->CreateSpriteSheet(ID_TEX_SIMON1);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(0);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(0); 	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_IDLE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(0);
	ani->Add(1);
	ani->Add(2);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_WALKING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(0);
	ani->Add(1);
	ani->Add(2); 	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_WALKING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(11);
	ani->Add(12);
	ani->Add(13);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_RUNNING_RIGHT, ani);

	ani = new CAnimation(50);	// Mario runs faster hence animation speed should be faster
	ani->Add(11);
	ani->Add(12);
	ani->Add(13);	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_RUNNING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(4);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_JUMP_WALK_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(4);	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_JUMP_WALK_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(15);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_JUMP_RUN_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(15);	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_JUMP_RUN_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(16);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_SIT_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(16); 	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_SIT_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(8);
	ani->SetDirection(-1);
	animations->Add(ID_ANI_SIMON_BRACE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(8);	ani->SetDirection(1);
	animations->Add(ID_ANI_SIMON_BRACE_LEFT, ani);
	

//	ani = new CAnimation(100);
//	ani->CreateFrameSheet(ID_TEX_SIMON);
//	ani->SetDefaultFrameTime(ID_ANI_SIMON_RUNNING_RIGHT, ID_ANI_SIMON_BRACE_RIGHT, 50);
//	ani->SetDefaultFrameTime(ID_ANI_SIMON_RUNNING_LEFT, ID_ANI_SIMON_IDLE_LEFT, 50);
//	animations->Add(ID_TEX_SIMON, ani);

	simon = new CSimon(SIMON_START_X, SIMON_START_Y);
	objects.push_back(simon);

//	ani = animations->Get(0);
	
//	ani = new CAnimation(100);
//	ani->CreateFrameSheet(ID_TEX_MISC);
//	animations->Add(ID_TEX_MISC, ani);

//	ani = animations->Get(0);

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	if (texMisc == nullptr) {
		DebugOut(L"[ERROR] texMisc is NULL! ID_TEX_MISC chưa được load hoặc không hợp lệ\n");
	}

	sprites->Add(ID_SPRITE_BRICK, 0, 0, 32, 32, texMisc);

//	sprites->Add(ID_SPRITE_BRICK, 372, 153, 372 + 15, 153 + 15, texMisc);
	LPSPRITE testBrickSprite = sprites->Get(ID_SPRITE_BRICK);
	if (testBrickSprite == nullptr) {
		DebugOut(L"[ERROR] testBrickSprite is NULL! ID_SPRITE_BRICK có thể chưa được thêm đúng\n");
	}

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_BRICK);
	animations->Add(ID_ANI_BRICK, ani);

	CBrick* b = new CBrick(BRICK_X, BRICK_Y);
	objects.push_back(b);


}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}