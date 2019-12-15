#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
    width = height = 0;
	vx = vy = 0;
	nx = 1;
    ny = 1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
//void CGameObject::CalcPotentialCollisions(
//	vector<LPGAMEOBJECT> *coObjects, 
//	vector<LPCOLLISIONEVENT> &coEvents)
void CGameObject::CalcPotentialCollisions(
	vector<CGameObject*> coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	//for (UINT i = 0; i < coObjects->size(); i++)
	for (UINT i = 0; i < coObjects.size(); i++)
	{
		//LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects.at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)t - (int)b;

    D3DXVECTOR3 p = ViewPort::getInstance()->getPositionInViewPort(new D3DXVECTOR3(l + width / 2, t - height / 2, 0));
    D3DXVECTOR3 center = D3DXVECTOR3(this->width / 2, this->height / 2, 0);
	CGame::GetInstance()->Draw(p.x, p.y, bbox, rect.left, rect.top, rect.right, rect.bottom, &center, 128);
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

bool CGameObject::checkOverlap(float l1, float t1, float r1, float b1, float l2, float t2, float r2, float b2)
{
    //Check horizontal aspect
    if (l1 > r2 || l2 > r1)
        return false;

    //Check vertical aspect
    if (t1 < b2 || t2 < b1)
        return false;

    return true;
}


CGameObject::~CGameObject()
{

}