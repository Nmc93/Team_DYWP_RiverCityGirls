#include "pch.h"
#include "coin.h"

coin::coin()
{
}

coin::~coin()
{
}




HRESULT coin::init()
{

    _coin = IMAGEMANAGER->addFrameImage("coin", "image/object/gold_coin_spin.bmp", 512, 512, 4, 4, true, RGB(255, 0, 255));

  //  KEYANIMANAGER->addCoordinateFrameAnimation("coinMotion", "coin", 0, 17, 5, false, true);

	_count = _indexX = 0;
	return S_OK;
}

void coin::release()
{
}

void coin::update()
{
	_count++;

	if (_count % 7 == 0)
	{
		_coin->setFrameX(_indexX);
		_indexX++;
		if (_indexX >= IMAGEMANAGER->findImage("coin")->getMaxFrameX()) _indexX = 0;
	}
}

void coin::drop()
{
}

void coin::render()
{
	_coin->frameRender(getMemDC(), 600, 600);
}

