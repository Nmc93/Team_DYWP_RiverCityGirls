#include "pch.h"
#include "money.h"


money::money()
{
}

money::~money()
{
}

HRESULT money::init(MONEYSTATE st, POINT ptxy)
{

	state = st;

	_count = _indexX = 0;


	if (state == COIN)
	{
		img = IMAGEMANAGER->addFrameImage("coin", "image/object/gold_coin_spin.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));

		//  KEYANIMANAGER->addCoordinateFrameAnimation("coinMotion", "coin", 0, 17, 5, false, true);
	}

	if (state == BILL)
	{
		img = IMAGEMANAGER->addFrameImage("bill", "image/object/money_green.bmp", 576, 432, 4, 4, true, RGB(255, 0, 255));
	}

	_sX = ptxy.x;
	_sY = ptxy.y;

	x = _sX;
	y = _sY - img->getFrameWidth() / 2;

	RC = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	_isJump = true;
	_gravity = 0.5f;
	_jumpPower = 5;




	return S_OK;
}


void money::release()
{
}

void money::update()
{
	RC = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	drop();

	_count++;

	if (_isJump)
	{
		y -= _jumpPower;
		_jumpPower -= _gravity;
	}
	else
	{
		x = _sX;
		y = _sY - img->getFrameHeight() / 2;
		_jumpPower = 0;
	}


	if (RC.bottom > _sY)
	{
		_jumpPower = 0;

		_isJump = false;
	}


	if (_count % 7 == 0)
	{
		img->setFrameX(_indexX);
	
		if (state == COIN)
		{
			_indexX++;

			if (_indexX >= img->getMaxFrameX()) _indexX = 0;
		}
		else if (state == BILL)
		{
			if (_indexX >= IMAGEMANAGER->findImage("bill")->getMaxFrameX()) _indexX = 0;
			if (_isJump == true)
			{
				_indexX++;
			}

		}
	}
}

void money::drop()
{

}

void money::render()
{
	img->frameRender(getMemDC(), RC.left, RC.top);
}
