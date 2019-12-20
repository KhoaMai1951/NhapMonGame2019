#include "MenuScene.h"

MenuScene::MenuScene()
{

};

void MenuScene::Initialize()
{
    ViewPort::getInstance()->setPositionWorld(D3DXVECTOR2(0, SCREEN_HEIGHT));
    Sound::getInstance()->play("SCENE_MENU", true, 0);

    menuMap = new CMap();
    menuMap->AddAnimation(ANI_MAIN_MENU);
    menuMap->SetPosition(0, 288);

    blade_pointer = new MovingObject();
    blade_pointer->AddAnimation(ANI_BLADE_POINTER_HUD);
    blade_pointer->SetPosition(90, 164);
	blade_pointer->vx = 0.08;
}

void MenuScene::Update(DWORD dt)
{
    CGame* game = CGame::GetInstance();
    if (game->IsKeyPress(DIK_RETURN))
    {
        Sound::getInstance()->play("MENU_SELECT", false, 1);
        if (choosing == 0)
            next_scene = SCENE_SULTAN;
        else
            next_scene = SCENE_BOSS;
        Sound::getInstance()->stop("SCENE_MENU");
    }

    if (choosing == 0)
    {
        if (game->IsKeyPress(DIK_UP) || game->IsKeyPress(DIK_DOWN))
        {
            Sound::getInstance()->play("MENU_CHANGE", false, 1);
            choosing = 1;
            blade_pointer->y = 144;
        }
    }
    else if (choosing == 1)
    {
        if (game->IsKeyPress(DIK_UP) || game->IsKeyPress(DIK_DOWN))
        {
            Sound::getInstance()->play("MENU_CHANGE", false, 1);
            choosing = 0;
            blade_pointer->y = 164;
        }
    }
        
	if (blade_pointer->x + 36 > 135)
	{
		blade_pointer->x = 135 - 36;
		blade_pointer->vx = -0.08;
	}
	if (blade_pointer->x < 85)
	{
		blade_pointer->x = 85;
		blade_pointer->vx = 0.08;
	}
	blade_pointer->x += blade_pointer->vx * dt;
}

void MenuScene::Render()
{
    LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
    LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackBuffer();
    LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

    if (d3ddv->BeginScene())
    {
        // Clear back buffer with a color
        d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

        spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        menuMap->Render();
        blade_pointer->Render();

        spriteHandler->End();
        d3ddv->EndScene();
    }

    // Display back buffer content to the screen
    d3ddv->Present(NULL, NULL, NULL, NULL);
}