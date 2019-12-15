#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include"ViewPort.h"
#include "GameObject.h"
#include "debug.h"
#include <vector>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_BUFFER_SIZE 256
/*
Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class CGame
{
	ViewPort* camera = NULL;

	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

    BYTE  keyStates[256];			// DirectInput keyboard state buffer 
    BYTE  prevStates[256];			// DirectInput keyboard state buffer 

	//DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
    //LPKEYEVENTHANDLER keyHandler;

public:
    //std::vector<CGameObject*> vector_apple;
	//void InitKeyboard(LPKEYEVENTHANDLER handler);
    void InitKeyboard();
	void Init(HWND hWnd);
	HWND getCurrentHWND() { return hWnd; }
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DXVECTOR3 *center, int alpha = 255);

	int IsKeyDown(int KeyCode);
    int IsKeyPress(int KeyCode);
	void ProcessKeyboard();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,			// static top					
		float sr,			// static right
		float sb,			// static bottom
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame * GetInstance();



	~CGame();
};

#endif


