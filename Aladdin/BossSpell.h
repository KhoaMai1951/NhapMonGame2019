//#ifndef BOSS_SPELL_H
//#define BOSS_SPELL_H
//
//#include "set"
//#include "SpatialGrid.h"
//#include "Enemy.h"
//#include "Ground.h"
//#include "debug.h"
//
//
//#define BOSS_SPELL_SPEED 0.10f
//#define BBOX_WIDTH 80//101
//#define BBOX_HEIGHT 35 //53
//enum BossSpellAni
//{
//	BOSS_FLAME_ANI,
//};
//
//class BossSpell : public CGameObject
//{
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
//	virtual void Render();
//
//public:
//	BossSpell() : CGameObject()
//	{
//		vx = 0;
//		vy = 0;
//		width = BBOX_WIDTH;
//		height = BBOX_HEIGHT;
//	}
//	virtual void SetState(int state);
//	void InsertToGrid() { SpatialGrid::GetInstance()->Insert(this); }
//};
//
//#endif // ! BONE_H