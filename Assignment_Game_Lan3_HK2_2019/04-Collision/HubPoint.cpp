#include "HubPoint.h"

HubPoint::HubPoint()
{
}


HubPoint::~HubPoint()
{
}

void HubPoint::Add(int index, LPCWSTR path)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 _texture;

	HRESULT result = D3DXGetImageInfoFromFile(path, &info);
	if (result != D3D_OK)
	{
		_RPT1(0, "[ERROR] GetImageInfoFromFile failed: %s\n", path);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		path,						        // Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&_texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	_listTexture[index] = _texture;

	_RPT1(0, "[INFO] Texture loaded Ok: %s \n", path);
}

void HubPoint::Render()
{
	CGame::GetInstance()->Draw(_x - 80, _y, _listTexture[_point01 / 10], 0, 0, 7, 10);

	CGame::GetInstance()->Draw(_x - 70, _y, _listTexture[_point01 % 10], 0, 0, 7, 10);

	CGame::GetInstance()->Draw(_x + 70, _y, _listTexture[_point02 / 10], 0, 0, 7, 10);

	CGame::GetInstance()->Draw(_x + 80, _y, _listTexture[_point02 % 10], 0, 0, 7, 10);

}

void HubPoint::Update(DWORD)
{
	_point01 = CGame::GetInstance()->getPointP1();
	_point02 = CGame::GetInstance()->getPointP2();
}
