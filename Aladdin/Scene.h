#ifndef scene_h
#define scene_h

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Health.h"
#include "Characters.h"
#include "HUD.h"

#include "Map.h"
#include "Game.h"
#include "ViewPort.h"
#include "Sprites.h"
#include "Textures.h"
#include "SpatialGrid.h"
#include "ResourceLoader.h"
#include "Aladdin.h"
#include "Skeleton.h"
#include "Sound.h"
#include "define.h"

using namespace std;

enum LEVEL
{
    SCENE_SULTAN,
    SCENE_BOSS,
    SCENE_MENU,
    SCENE_COMPLETE
};
class Aladdin;
class Skeleton;
class Scene
{
protected:
    Aladdin *aladdin;
    vector<LPGAMEOBJECT> map_vector;
    vector<LPGAMEOBJECT> front_objects;
    vector<LPGAMEOBJECT> objects; //All collision object and aladdin
    ViewPort * camera = ViewPort::getInstance();
	Health* healthHUD;
	Characters* characterHUD;
	HUD *lifeHUD,*rubyHUD, *appleHUD;

public:
    int next_scene = SCENE_MENU;
    float save_x, save_y;
    Scene()
    {
        //next_scene = SCENE_SULTAN;
        //tile_count = 0;

#pragma region
		healthHUD = new Health();
		healthHUD->AddAnimation(ANI_HEALTH_1);
		healthHUD->AddAnimation(ANI_HEALTH_2);
		healthHUD->AddAnimation(ANI_HEALTH_3);
		healthHUD->AddAnimation(ANI_HEALTH_4);
		healthHUD->AddAnimation(ANI_HEALTH_5);
		healthHUD->AddAnimation(ANI_HEALTH_6);
		healthHUD->AddAnimation(ANI_HEALTH_7);
		healthHUD->AddAnimation(ANI_HEALTH_8);
		healthHUD->AddAnimation(ANI_HEALTH_9);
		
		lifeHUD = new HUD();
		lifeHUD->AddAnimation(ANI_FACE_HUD);
		appleHUD = new HUD();
		appleHUD->AddAnimation(ANI_APPLE_HUD);
		rubyHUD = new HUD();
		rubyHUD->AddAnimation(ANI_RUBY_HUD);

		characterHUD = new Characters();
		for (int i = 0; i <= 19; i++)
		{
			characterHUD->AddAnimation(5100 + i);
		}
#pragma endregion Load animation to HUDs
    };
    virtual void Update(DWORD) {};
    virtual void Render() {};

    virtual ~Scene()
    {
        for (int i = objects.size() - 1; i >= 0; --i)
            delete objects[i];
        objects.clear();
        SpatialGrid::GetInstance()->Clear();
        for (int i = map_vector.size() - 1; i >= 0; --i)
            delete map_vector[i];

       /* CSprites* sprites = CSprites::GetInstance();
        for (int i = 0; i < tile_count; i++)
            delete (sprites->Get(TILE_INDEX + i));*/
    };

    virtual void Initialize() {};
    void SetSaveLocation(float _x, float _y) { save_x = _x; save_y = _y; }

    void DrawTextHUD(string text, float x, float y, bool isBigSize = false)
	{
		for (int i = 0; i < text.size(); i++)
		{
			int asciiCode = (int)text[i];	//get ascii code of the number
			int charAni;
			if (asciiCode >= 48 && asciiCode <= 57)
			{
				charAni = asciiCode - 48;	//switch ascii code to animation index
			}
			/*else if (asciiCode >= 97 && asciiCode <= 122)
			{
				charAni = asciiCode - 87;
			}
			else if (asciiCode == 32)
			{
				charAni = asciiCode + 4;
			}*/


			Characters* temp_char = this->characterHUD;
            if (isBigSize)
            {
                if (charAni >= 0 && charAni <= 9)
                    charAni += 10;  //not include alphabet
            }
            temp_char->ani = charAni;

			temp_char->x = x + i * 14;
			temp_char->y = y;
			temp_char->Render();
		}
	}

};
#endif // !scene_h


