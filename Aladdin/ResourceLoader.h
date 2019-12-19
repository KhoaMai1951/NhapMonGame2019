﻿#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <string>

#include "Apple.h"
#include "Ruby.h"
#include "Genie.h"
#include "Vase.h"
#include "LifeHeal.h"

#include "Guard0.h"
#include "Guard1.h"
#include "Skeleton.h"
#include "Bat.h"

#include "Step.h"
#include "SpikeTrap.h"
#include "WreckingBall.h"
#include "Ground.h"
#include "Chains.h"

#include "Map.h"
#include "define.h"
#include "Textures.h"

class ResourceLoader
{
public:
	~ResourceLoader();
	ResourceLoader();

	static ResourceLoader* GetInstance();
	void LoadObjectFromFile(string FileName, vector<LPGAMEOBJECT> &objects, int first_index, int scene);
	void LoadMapFromFile(string FileName, LPDIRECT3DTEXTURE9 texMap, vector<LPGAMEOBJECT>& map_vector, int scene);

    static void LoadSprite();
	static void CreateAnimation();
    void ChangeYtoDecart(float& y, int scene);
	static void LoadMusic();

	vector<int> read_map(string file_path);
	void load_tile_map(LPDIRECT3DTEXTURE9 tile_set, string file_path, vector<LPGAMEOBJECT>& map_vector, int scene);

private:
	static ResourceLoader* _instance;

};
#endif

