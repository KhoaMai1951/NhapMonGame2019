#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "GameObject.h"
#include <unordered_map> 

class HubPoint
{
private:
	int _x, _y;

	// texture arry
	std::unordered_map<int, LPDIRECT3DTEXTURE9> _listTexture;

	// point of 2 players
	int _point01 = 0, _point02 = 0;



public:
	HubPoint();
	~HubPoint();

	void SetPos(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Add(int index, LPCWSTR path);

	void Render();

	void Update(DWORD);
};

