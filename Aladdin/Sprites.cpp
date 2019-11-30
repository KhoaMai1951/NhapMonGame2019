#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
    this->width = right - left;
    this->height = bottom - top;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
    D3DXVECTOR3 p = ViewPort::getInstance()->getPositionInViewPort(new D3DXVECTOR3(x + width/2, y - height/2, 0));
    D3DXVECTOR3 center = D3DXVECTOR3(width / 2, height / 2, 0);
    CGame::GetInstance()->Draw(p.x, p.y, texture, left, top, right, bottom, &center, alpha);
   /* D3DXVECTOR3 p = ViewPort::getInstance()->getPositionInViewPort(new D3DXVECTOR3(x , y, 0));
    CGame::GetInstance()->Draw(p.x, p.y, texture, left, top, right, bottom, new D3DXVECTOR3(0,0,0), alpha);*/
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}



void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha, int restart)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = restart;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::Render(float &x, float &y, long &lastFrameWidth, long &lastFrameHeight, int alpha, int restart)
{
    DWORD now = GetTickCount();
    if (currentFrame == -1)
    {
        currentFrame = 0;
        lastFrameTime = now;
    }
    else
    {
        DWORD t = frames[currentFrame]->GetTime();
        if (now - lastFrameTime > t)
        {
            currentFrame++;
            lastFrameTime = now;
            if (currentFrame == frames.size()) currentFrame = restart;

            //int curWidth = frames[currentFrame]->GetSprite()->width;
            //int curHeight = frames[currentFrame]->GetSprite()->height;

            ////x += (curWidth - lastFrameWidth) / 2;
            ////y += (curHeight - lastFrameHeight) / 2;

            ////x += (curWidth - lastFrameWidth) / 2;
            //y += curHeight - lastFrameHeight;

            //lastFrame = currentFrame;
            //lastFrameWidth = curWidth;
            //lastFrameHeight = curHeight;
        }

    }

    int curWidth = frames[currentFrame]->GetSprite()->width;
    int curHeight = frames[currentFrame]->GetSprite()->height;

    //x += (curWidth - lastFrameWidth) / 2;
    //y += (curHeight - lastFrameHeight) / 2;

    //x += (curWidth - lastFrameWidth) / 2;
    //x -= curWidth - lastFrameWidth;
    y += curHeight - lastFrameHeight ;

    lastFrame = currentFrame;
    lastFrameWidth = curWidth;
    lastFrameHeight = curHeight;

    //if (currentFrame >= 0)
    //{
    //    int curWidth = frames[currentFrame]->GetSprite()->width;
    //    int curHeight = frames[currentFrame]->GetSprite()->height;

    //    x += (curWidth - lastFrameWidth) / 2;
    //    y += (curHeight - lastFrameHeight) / 2;

    //    lastFrameWidth = curWidth;
    //    lastFrameHeight = curHeight;
    //    lastFrame = currentFrame;

    //    //int curHeight = frames[currentFrame]->GetSprite()->height;

    //    //if (curHeight > lastFrameHeight)
    //    //{
    //    //    y += curHeight - lastFrameHeight;
    //    //}
    //    //else
    //    //{
    //    //    y += lastFrameHeight - curHeight;
    //    //    //y += 0.0005 * 16;
    //    //}
    //    //lastFrameHeight = curHeight;
    //}

 /*   lastFrameWidth = frames[currentFrame]->GetSprite()->width;
    lastFrameHeight = frames[currentFrame]->GetSprite()->height;*/

    frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}