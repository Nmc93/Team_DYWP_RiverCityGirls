#include "pch.h"
#include "camera.h"

HRESULT camera::init()
{
	

	_x = 0;
	_y = 0;

	

	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
	


	//_pixelImg->setX(_x);
}

void camera::render()
{
	//_pixelImg->setX(_x);
	
	//_img->render(getMemDC(), 0, 0, _x, _y, WINSIZEX, WINSIZEY);

	/*char str[128];
	sprintf_s(str, "¾îÂ¼ : %f", _pixelImg->getX());
	TextOut(getMemDC(), 0, 500, str, strlen(str));*/

	/*
	char str[128];
	sprintf_s(str, "°¡·Î : %d, _x : %d", _img->getWidth() - WINSIZEX, _x);
	TextOut(getMemDC(), 0, 20, str, strlen(str));
	*/
}


