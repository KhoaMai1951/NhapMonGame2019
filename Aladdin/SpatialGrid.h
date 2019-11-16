#pragma once
#include <cmath>
#include <set>
#include "GameObject.h"
#include <map>
#include "define.h"
#include "ViewPort.h"

class SpatialGrid
{
	static SpatialGrid* instance; //<-- singleton

	float CellSize;
	map<string, vector<CGameObject*>> Grid;

	string IndexMakeKey(stringstream&, float&, float&);

public:
	SpatialGrid() { SetCell(CELL_SIZE); };
	void Clear();
	void SetCell(int);
	void Insert(CGameObject*);
	void Index(CGameObject*, float&, float&, float&, float&);
	set<CGameObject*> Get(float, float, float, float);
	static SpatialGrid* GetInstance();
};