﻿#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <string>

//#include "Mario.h"
//#include "Goomba.h"
//#include "Brick.h"
#include "Apple.h"
#include "Ground.h"
#include "Map.h"
#include "define.h"
#include "Textures.h"

class ResourceLoader
{
public:
	~ResourceLoader();
	ResourceLoader();

	static ResourceLoader* GetInstance();
	void LoadObjectFromFile(string FileName, vector<LPGAMEOBJECT> &objects);
	void LoadMapFromFile(string FileName, LPDIRECT3DTEXTURE9 texMap, vector<LPGAMEOBJECT>& map_vector);

    static void LoadSprite();
	static void CreateAnimation();
    void ChangeYtoDecart(float& y);

	vector<int> read_map(string file_path);
	void load_tile_map(LPDIRECT3DTEXTURE9 tile_set, string file_path, vector<LPGAMEOBJECT>& map_vector);

private:
	static ResourceLoader* _instance;

};

