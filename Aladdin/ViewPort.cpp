#include "ViewPort.h"

ViewPort* ViewPort::_instance = NULL;
ViewPort::ViewPort(void)
{
	_positionWorld.x = 0;
	_positionWorld.y = 0;
}

ViewPort::ViewPort(float x, float y)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
}

ViewPort::ViewPort(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

ViewPort::~ViewPort(void)
{
}

ViewPort* ViewPort::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new ViewPort(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
		
	return _instance;
}

void ViewPort::setPositionWorld(D3DXVECTOR2 position)
{
	if (_positionWorld != position)
		_positionWorld = position;
}

D3DXVECTOR2 ViewPort::getPositionWorld()
{
	return _positionWorld;
}

float ViewPort::getWidth()
{
	return _width;
}

float ViewPort::getHeight()
{
	return _height;
}

D3DXVECTOR3 ViewPort::getPositionInViewPort(D3DXVECTOR3* position)
{
	D3DXMATRIX mt;
	D3DXVECTOR4 posViewPort;

	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -_positionWorld.x;
	mt._42 = _positionWorld.y;

	D3DXVec3Transform(&posViewPort, position, &mt);

	return D3DXVECTOR3(posViewPort.x, posViewPort.y, posViewPort.z);
}

bool ViewPort::isContain(float left, float top, float right, float bottom)
{
	/* if (rect.right < _positionWorld.x)
		 return false;
	 if (rect.bottom > _positionWorld.y)
		 return false;
	 if (rect.left > _positionWorld.x + _width)
		 return false;
	 if (rect.top < _positionWorld.y - _height)
		 return false;
	 return true;*/

	RECT cam_rect, object_rect;
	cam_rect.left = _positionWorld.x;
	cam_rect.top = _positionWorld.y;
	cam_rect.right = _positionWorld.x + SCREEN_WIDTH;
	cam_rect.bottom = _positionWorld.y - SCREEN_HEIGHT;

	object_rect.left = left;
	object_rect.top = top;
	object_rect.right = right;
	object_rect.bottom = bottom;

	return checkOverlap(cam_rect, object_rect);
}

RECT ViewPort::getBounding()
{
	RECT rect;

	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.bottom = rect.top - _height;
	rect.right = rect.left + _width;

	return rect;
}

bool ViewPort::checkOverlap(RECT r1, RECT r2)
{
	//Check horizontal aspect
	if (
		r1.left > r2.right || r2.left > r1.right)
		return false;

	//Check vertical aspect
	if (r1.top < r2.bottom || r2.top < r1.bottom)
		return false;

	return true;
}

