#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"

#include "SultansDungeon_Scene.h"
#include "ResourceLoader.h"

CGame *game;
Scene *scene = NULL;

//class CSampleKeyHander: public CKeyEventHandler
//{
//	virtual void KeyState(BYTE *states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander * keyHandler; 
//
////Nhấn thả
//void CSampleKeyHander::OnKeyDown(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	//switch (KeyCode)
//	//{
//	//case DIK_SPACE: // jump
//	//	mario->SetState(MARIO_STATE_JUMP);
//	//	break;
//	//case DIK_Z: // reset
//	//	mario->SetState(MARIO_STATE_IDLE);
//	//	mario->SetLevel(MARIO_LEVEL_BIG);
//	//	mario->SetPosition(50.0f,100.0f);
//	//	mario->SetSpeed(0, 0);
//	//	break;
//	//}
//}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//}
//
////Nhấn giữ
//void CSampleKeyHander::KeyState(BYTE *states)
//{
//	//// disable control key when Mario die 
//	//if (mario->GetState() == MARIO_STATE_DIE) return;
//	//if (game->IsKeyDown(DIK_RIGHT))
//	//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
//	//else if (game->IsKeyDown(DIK_LEFT))
//	//	mario->SetState(MARIO_STATE_WALKING_LEFT);
//	//else
//	//	mario->SetState(MARIO_STATE_IDLE);
//}

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
			
			scene->Update(dt);
			scene->Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	//keyHandler = new CSampleKeyHander();
	//game->InitKeyboard(keyHandler);  
    game->InitKeyboard();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*1.8, SCREEN_HEIGHT*1.8, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    ResourceLoader::CreateAnimation();
    scene = new SultansDungeon_Scene();
    scene->Initialize();

	Run();

	return 0;
}