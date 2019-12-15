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
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);

    //IF player in bat's attack range
    if (state == SKELETON_STATE_NOT_CREATE)
    {
        if ((player_x + 40 >= x - SKELETON_START_RANGE_HORIZONTAL) && (player_x <= x + width + SKELETON_START_RANGE_HORIZONTAL))
        {
            if ((player_y >= y - height - SKELETON_START_RANGE_VERTICAL) && (player_y - 48 <= y + SKELETON_START_RANGE_VERTICAL))
            {
                SetState(SKELETON_STATE_CREATE);
            }
        }
    }
    

    if (state == SKELETON_STATE_CREATE)
    {
        if (hitpoint <= 0)
            SetState(SKELETON_STATE_DEAD);
        else if (animations[ani]->currentFrame == 20 && !exploded)
            Explode();
    }   
    else if (state == SKELETON_STATE_DEAD)
    {
        if(animations[ani]->currentFrame == 9)
            isDead = true;
        return;
    } 

}

void Skeleton::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case SKELETON_STATE_NOT_CREATE:
        break;
    case SKELETON_STATE_CREATE:
        idle_start = GetTickCount();
        animations[SKELETON_ANI_CREATE]->ResetAnimation();
        break;
    case SKELETON_STATE_DEAD:
        Sound::getInstance()->play("ENEMY_DEAD", false, 1);
        //repostion object for explode, skeleton sprite(95,91), explode sprite (90,57)
        x = x + (95 - 90) / 2;
        y = y + (91 - 57) / 2;
        animations[SKELETON_ANI_DEAD]->ResetAnimation();
        break;
    }
}

void Skeleton::Render()
{
    int restart_frame = 0;
    switch (state)
    {
    case SKELETON_STATE_NOT_CREATE:
        return;
    case SKELETON_STATE_CREATE:
    {
        restart_frame = 0;
        ani = SKELETON_ANI_CREATE; break;
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

void Skeleton::Explode()
{
    Sound::getInstance()->play("SKELETON_EXPLODE", false, 1);
    SetState(SKELETON_STATE_DEAD);
    exploded = true;
	//bay phải
	for (int i = -2; i < 2; i++)
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
	for (int i = -2; i < 2; i++)
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