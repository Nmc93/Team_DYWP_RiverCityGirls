#include "pch.h"
#include "pixelCol.h"
#include "stageManager.h"

HRESULT pixelCol::init(RECT rc)
{

	_x = (rc.left + rc.right) / 2;
	_y = (rc.top + rc.bottom) / 2;

	_isMove = true;

    return S_OK;
}

void pixelCol::release()
{
}

void pixelCol::update(RECT rc)
{
	// 중심 좌표
	_x = (rc.left + rc.right) / 2;
	_y = (rc.top + rc.bottom) / 2;

	int left = rc.left;
	int right = rc.right;
	int top = rc.top;
	int bottom = rc.bottom;
	
	// 왼쪽
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = left - 5; i < left + 5; ++i)
		{
			COLORREF color = GetPixel(_sM->getPixelImage()->getMemDC(), i + _cam->getX(), _y + _cam->getY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 0 && g == 255 && b == 255))
			{
				_isMove = true;
				break;
			}
			else
			{
				_isMove = false;
				break;
			}
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// 오른쪽
		for (int i = right + 5; i > right - 5; --i)
		{
			COLORREF color = GetPixel(_sM->getPixelImage()->getMemDC(), i + _cam->getX(), _y + +_cam->getY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

	
			if (!(r == 0 && g == 255 && b == 255))
			{
				_isMove = true;
				//break;
			}
			else
			{
				_isMove = false;
				break;
			}
		}
	}

	// 위쪽
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		for (int i = top - 5; i < top + 5; ++i)
		{
			COLORREF color = GetPixel(_sM->getPixelImage()->getMemDC(), _x + _cam->getX(), i + +_cam->getY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if (!(r == 0 && g == 255 && b == 255))
			{
				_isMove = true;
				//break;
			}
			else
			{
				_isMove = false;
				break;
			}
		}
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		// 아래쪽
		for (int i = bottom + 5; i > bottom - 5; --i)
		{
			COLORREF color = GetPixel(_sM->getPixelImage()->getMemDC(), _x + _cam->getX(), i + _cam->getY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if (!(r == 0 && g == 255 && b == 255))
			{
				_isMove = true;
				//break;
			}
			else
			{
				_isMove = false;
				break;
			}
		}
	}

	

}

void pixelCol::render()
{
	if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	{
		char str[128];
		sprintf_s(str, " _isMove : %d", _isMove);
		TextOut(getMemDC(), 0, 320, str, strlen(str));

		sprintf_s(str, " _x : %f", _cam->getX());
		TextOut(getMemDC(), 0, 340, str, strlen(str));

		sprintf_s(str, " _px : %d", _x);
		TextOut(getMemDC(), 0, 400, str, strlen(str));

		sprintf_s(str, " _py : %d", _y);
		TextOut(getMemDC(), 0, 420, str, strlen(str));

		sprintf_s(str, " _imgx : %f", _sM->getPixelImage()->getX());
		TextOut(getMemDC(), 0, 360, str, strlen(str));
	}
}
