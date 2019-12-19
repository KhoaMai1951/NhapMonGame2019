﻿#include "Boss.h"
#include "Boss_Scene.h"
void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isHumanForm)
		width = BBOX_WIDTH;
	else
		width = BBOX_WIDTH2;
	height = lastFrameHeight;

	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead) return;
	CGameObject::Update(dt, coObjects);

	if (GetTickCount() - idle_start > 5000 && isHumanForm)
	{
		//laugh
		Sound::getInstance()->play("JAFAR_LAUGH", false, 1);
		idle_start = GetTickCount();
	}

    if (isHumanForm && hitpoint < BOSS_MAX_HITPOINT / 2)
        isHumanForm = false;

	if (!isHumanForm && (animations[ani]->currentFrame == 10) && !attacking)
	{
		Sound::getInstance()->play("JAFAR_SNAKE", false, 1);
		BossFlame* boss_flame = new BossFlame();
		boss_flame->AddAnimation(BOSS_FLAME_RIGHT);
		boss_flame->AddAnimation(BOSS_FLAME_LEFT);
		boss_flame->nx = nx;
        if (nx == 1)
        {
            boss_flame->x = x + (width / 2);
            boss_flame->y = y - (height / 2);
        }
        else if (nx == -1)
        {
            boss_flame->x = x - BOSS_FLAME_WIDTH + +(width / 2);
            boss_flame->y = y - (height / 2);
        }
		boss_flame->id = ((Boss_Scene*)scene)->grid_id++;
		boss_flame->InsertToGrid();
		((Boss_Scene*)scene)->vector_boss_flame.push_back(boss_flame);
		attacking = true;
	}
	else if (!isHumanForm && (animations[ani]->currentFrame == 11))
		attacking = false;
    else
    {
        AddBossSpell();
    }

	if (player_x < x)
	{
		nx = -1;
	}
	else if (player_x > x + width / 2)
	{
		nx = 1;
	}

	if (CGame::GetInstance()->IsKeyPress(DIK_G))
		ChangeForm();

	//if state == !isHumanForm -> if(animations[ani]->currentFrame == frame cuoi) -> create boss flame
	//if(nx > 0) setposition .... else

	
}

void Boss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_ATTACK:
		break;
	case BOSS_STATE_ATTACK2:
		break;
	case BOSS_STATE_HURT:
		break;
	}
}

void Boss::Render()
{
	if (isDead) return;
	int restart_frame = 0;
	if (isHumanForm)
	{
		if (nx > 0)
		{
			SetPosition(400.0f, 165.0f);
			ani = BOSS_ANI_ATTACK1_RIGHT;
		}
		else
		{
			SetPosition(385.0f, 165.0f);
			ani = BOSS_ANI_ATTACK1_LEFT;
		}	
	}
	else
	{
		if (nx > 0)
		{
			SetPosition(370.0f, 178.0f);
			ani = BOSS_ANI_ATTACK2_RIGHT;
		}
		else
		{
			SetPosition(390.0f, 178.0f);
			ani = BOSS_ANI_ATTACK2_LEFT;
		}
	}
		
	//animations[ani]->Render(x, y, alpha, restart_frame);
	animations[ani]->Render(x, y, width, lastFrameWidth, lastFrameHeight, 255, restart_frame, nx);

	RenderBoundingBox();
}

void Boss::AddBossSpell()
{
    if (isHumanForm && (animations[ani]->currentFrame != lastFrame))
    {
        Sound::getInstance()->play("JAFAR_TRACTOR", false, 1);
        BossSpell* spell = new BossSpell();
        spell->AddAnimation(BOSS_SPELL);
        spell->AddAnimation(BOSS_SPELL_EXPLODE);
        spell->nx = nx;
        if (nx == 1)
        {
            spell->x = x + width;
            spell->leftSide = false;
        }  
        else if (nx == -1)
        {
            spell->x = x - 30;
            spell->leftSide = true;
        }
        spell->y = y - 10;
        spell->id = ((Boss_Scene*)scene)->grid_id++;
        spell->InsertToGrid();
        spell->SetState(BOSS_SPELL_STATE_FLYING);
        ((Boss_Scene*)scene)->vector_boss_spell.push_back(spell);
        lastFrame = animations[ani]->currentFrame;
    }
}