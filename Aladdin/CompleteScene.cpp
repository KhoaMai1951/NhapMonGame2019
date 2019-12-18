#include "CompleteScene.h"

CompleteScene::CompleteScene()
{

};

void CompleteScene::Initialize()
{
    ViewPort::getInstance()->setPositionWorld(D3DXVECTOR2(0, SCREEN_HEIGHT));
    Sound::getInstance()->play("LEVEL_COMPLETE", false, 1);

    completeMap = new CMap();
    completeMap->AddAnimation(ANI_LEVEL_COMPLETE);
    completeMap->SetPosition(0, 298);

    completeAladdin = new MovingObject();
    completeAladdin->AddAnimation(ANI_ALADDIN_LEVEL_COMPLETE);
    completeAladdin->SetPosition(400, 120);
    completeAladdin->vx = -0.1;

    completeAbu = new MovingObject();
    completeAbu->AddAnimation(ANI_ABU_LEVEL_COMPLETE);
    completeAbu->SetPosition(330, 95);
    completeAbu->vx = -0.1;
}

void CompleteScene::Update(DWORD dt)
{
    completeAladdin->Update(dt);
    completeAbu->Update(dt);
    if (completeAladdin->x < -30)
        next_scene = SCENE_MENU;
}

void CompleteScene::Render()
{
    LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
    LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackBuffer();
    LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

    if (d3ddv->BeginScene())
    {
        // Clear back buffer with a color
        d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

        spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        completeMap->Render();
        completeAladdin->Render();
        completeAbu->Render();

        spriteHandler->End();
        d3ddv->EndScene();
    }

    // Display back buffer content to the screen
    d3ddv->Present(NULL, NULL, NULL, NULL);
}