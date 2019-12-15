#include "Skeleton.h"
#include "SultansDungeon_Scene.h"
#include "Bone.h"

void Skeleton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    width = lastFrameWidth;
    height = lastFrameHeight;

    left = x;
    top = y;
    right = left + width;
    bottom = top - height;
    /*switch (state)
    {
    case STATE_IDLE:
        right = x + BBOX_WIDTH;
        bottom = y - BBOX_HEIGHT;
        break;
    default:
        right = x + BBOX_WIDTH;
        bottom = y - BBOX_HEIGHT;
    }*/
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);

    if(state != SKELETON_STATE_DEAD && hitpoint <= 0)
        SetState(SKELETON_STATE_DEAD);
    else if (state == SKELETON_STATE_DEAD)
    {
        if(animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    } 
    /*if (state == SKELETON_STATE_CREATE)
    {
        if (animations[ani]->currentFrame == 6)
        {
            SetState(SKELETON_STATE_EXPLODE);
        }
    }
    else if (state == SKELETON_STATE_EXPLODE)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 7000)
        {
            SetState(SKELETON_STATE_DEAD);
        }
    }
    else if (state == SKELETON_STATE_DEAD)
    {
        if (idle_start != 0 && GetTickCount() - idle_start > 8000)
        {
            SetState(SKELETON_STATE_CREATE);
            nx = -nx;
        }
    }*/

}

void Skeleton::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case SKELETON_STATE_CREATE:
        idle_start = GetTickCount();
        animations[SKELETON_ANI_CREATE]->ResetAnimation();
        break;
    case SKELETON_STATE_EXPLODE:
        animations[SKELETON_ANI_EXPLODE]->ResetAnimation();
        break;
    case SKELETON_STATE_DEAD:
        //repostion object for explode, skeleton sprite(95,91), explode sprite (90,57)
        x = x + (95 - 90) / 2;
        y = y + (91 - 57) / 2;
		AddFlyingBone();
        animations[SKELETON_ANI_DEAD]->ResetAnimation();
        break;
    }
}

void Skeleton::Render()
{
    int restart_frame = 0;
    switch (state)
    {
    case SKELETON_STATE_CREATE:
    {
        restart_frame = 0;
        ani = SKELETON_ANI_CREATE; break;
    }
    case SKELETON_STATE_EXPLODE:
    {
        restart_frame = 0;
        ani = SKELETON_ANI_EXPLODE; break;
    }
    case SKELETON_STATE_DEAD:
    {
        ani = SKELETON_ANI_DEAD; break;
    }
    }

    int alpha = 255;
    //animations[ani]->Render(x, y, alpha, restart_frame);
    animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, alpha, restart_frame, nx);

    //RenderBoundingBox();
}

void Skeleton::AddFlyingBone()
{
	//bay phải
	for (int i = 0; i < 4; i++)
	{
		Bone* bone = new Bone();
		bone->AddAnimation(BONE_FLYING);
		bone->nx = 1;
		bone->x = x + (width / 2);
		bone->y = y - (height / 2) - i * 5; // giảm 5 pixel mỗi xương
		bone->vy = i - 1;
		bone->SetState(BONE_STATE_FLYING);
		((SultansDungeon_Scene*)scene)->vector_bone.push_back(bone);
	}
	//bay trái
	for (int i = 0; i < 4; i++)
	{
		Bone* bone = new Bone();
		bone->AddAnimation(BONE_FLYING);
		bone->nx = -1;
		bone->x = x + (width / 2);
		bone->y = y - (height / 2) - i * 5; // giảm 5 pixel mỗi xương
		bone->vy = i - 1;
		bone->SetState(BONE_STATE_FLYING);
		((SultansDungeon_Scene*)scene)->vector_bone.push_back(bone);
		//DebugOut(L"Bone added to vector \n");
	}

	//bay lên
	for (int i = -2; i < 2; i++)
	{
		if (i == 0) continue; //skip 0
		Bone* bone = new Bone();
		bone->AddAnimation(BONE_FLYING);
		if (i < 0)
			bone->nx = -1;
		else if (i > 0)
			bone->nx = 1;
		bone->x = x + (width / 2) + i * 3;
		bone->y = y - (height / 2);
		bone->vy = 3;
		bone->SetState(BONE_STATE_FLYING);
		((SultansDungeon_Scene*)scene)->vector_bone.push_back(bone);
	}
}