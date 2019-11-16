#pragma once
#define __VIEWPORT_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "define.h"

/*
ViewPort là class dùng để chuyển hệ toạ độ top-left về hệ toạ độ đê-cac
là toạ độ camera trong thế giới game.
*/
class ViewPort
{
public:
	~ViewPort(void);
	ViewPort(void);
	ViewPort(float x, float y);
	ViewPort(float x, float y, float width, float height);


	static ViewPort* getInstance();
	void setPositionWorld(D3DXVECTOR2 position);
	D3DXVECTOR2 getPositionWorld();

	float getWidth();
	float getHeight();

	//decard to world
	D3DXVECTOR3 getPositionInViewPort(D3DXVECTOR3* position);

	// kiểm tra hcn có nằm trong màn hình không.
	bool isContain(float left, float top, float right, float bottom);
	/*
	Lấy kích thước của viewport bằng HCN, tinhs trong world lớn
	*/
	RECT getBounding();
	bool checkOverlap(RECT r1, RECT r2);
	RECT InvertY(float left, float top, float right, float bottom, float width, float height);

private:
	static ViewPort* _instance;
	D3DXVECTOR2 _positionWorld;
	float _width;
	float _height;
};

