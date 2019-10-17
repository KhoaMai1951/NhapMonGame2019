#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windowsx.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Brick.h"
#include "Ball.h"
#include "Bar.h"
#include "HubPoint.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Assignment 2"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_BALL 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_BAR 30
#define ID_TEX_BAR2 31

CGame *game;

CBall* ball;
CBar* bar1;
CBar* bar2;
HubPoint* scoreboard;

vector<LPGAMEOBJECT> objects;
HWND hWnd; //Main Window

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;
//Nhấn thả
void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

//Nhấn giữ
void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_X) || game->IsKeyDown(DIK_DOWN))
		bar1->SetState(BAR_MOVE_DOWN);
	else if (game->IsKeyDown(DIK_S) || game->IsKeyDown(DIK_UP))
		bar1->SetState(BAR_MOVE_UP);
	else 
		bar1->SetState(BAR_IDLE);
}

//Di chuyen chuot
POINT p;
void OnMouseMove(HWND hWnd)
{
    GetCursorPos(&p);
    ScreenToClient(hWnd, &p);
    bar2->Move(p.y/2);
}

void OnMouseDown()
{
    if(ball->GetState() == BALL_IDLE)
        ball->SetState(BALL_MOVING);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) { 
    case WM_MOUSEMOVE:
        OnMouseMove(hWnd);
        break;
    case WM_LBUTTONDOWN:
        OnMouseDown();
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BALL, L"textures\\ball.png",D3DCOLOR_XRGB(255, 255, 255));

	textures->Add(ID_TEX_BAR, L"textures\\bar.png", D3DCOLOR_XRGB(3, 26, 110));
    textures->Add(ID_TEX_BAR2, L"textures\\bar.png", D3DCOLOR_XRGB(3, 26, 110));

	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texBall = textures->Get(ID_TEX_BALL);

	// Ball
    sprites->Add(10001, 0, 0, 15, 15, texBall);		// idle right

	// Bar
	LPDIRECT3DTEXTURE9 texBar = textures->Get(ID_TEX_BAR);
	sprites->Add(40001, 133, 62, 144, 100, texBar);
    LPDIRECT3DTEXTURE9 texBar2 = textures->Get(ID_TEX_BAR2);
    sprites->Add(40002, 133, 62, 144, 100, texBar2);
	
	//--------------------------Animation---------------------------
	LPANIMATION ani;

	ani = new CAnimation(100);	// bar1
	ani->Add(40001);
	animations->Add(300, ani);

    ani = new CAnimation(100);	// bar2
    ani->Add(40002);
    animations->Add(301, ani);

	ani = new CAnimation(100);	// idle big right
	ani->Add(10001);
	animations->Add(400, ani);

    //--------------------------OBJECT---------------------------
	ball = new CBall();
	ball->AddAnimation(400);
	ball->SetPosition(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT/2 - 40);
	objects.push_back(ball);

	bar1 = new CBar();
	bar1->AddAnimation(300);
	bar1->SetPosition(130, SCREEN_HEIGHT / 2 - 40);
	objects.push_back(bar1);

    bar2 = new CBar();
    bar2->AddAnimation(301);
    bar2->SetPosition(SCREEN_WIDTH - 30, SCREEN_HEIGHT/2 - 40);
    objects.push_back(bar2);

    //Score
    scoreboard = new HubPoint();
    scoreboard->Add(0, L"textures\\Numbers 0-9\\0.png");
    scoreboard->Add(1, L"textures\\Numbers 0-9\\1.png");
    scoreboard->Add(2, L"textures\\Numbers 0-9\\2.png");
    scoreboard->Add(3, L"textures\\Numbers 0-9\\3.png");
    scoreboard->Add(4, L"textures\\Numbers 0-9\\4.png");
    scoreboard->Add(5, L"textures\\Numbers 0-9\\5.png");
    scoreboard->Add(6, L"textures\\Numbers 0-9\\6.png");
    scoreboard->Add(7, L"textures\\Numbers 0-9\\7.png");
    scoreboard->Add(8, L"textures\\Numbers 0-9\\8.png");
    scoreboard->Add(9, L"textures\\Numbers 0-9\\9.png");
    scoreboard->SetPos(SCREEN_WIDTH/2 - 10, 10);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{

	vector<LPGAMEOBJECT> coObjects; //Vector chứa các Object va chạm (trừ index 0)
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}

    scoreboard->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
        scoreboard->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
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
	wc.hIcon = NULL;
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
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}