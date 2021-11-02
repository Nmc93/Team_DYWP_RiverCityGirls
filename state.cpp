#include "pch.h"
#include "state.h"
#include "player.h"
#include "enemy.h"

HRESULT state::init()
{


	return S_OK;
}

void state::release()
{
}

void state::update()
{
	_wDir = _p->getWDir();
	_hDir = _p->getHDir();

	stateChange();
	setAni();
	
	_p->playerHit(_p, _vem, 40);

	KEYANIMANAGER->update();
}

void state::render()
{
	_p->stateRender(_motion);

	char str[128];
	sprintf_s(str, "dir : %d", _wDir);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
}

void state::findImage(const char* imageName)
{
	if (_img == NULL)
	{
		_motion->start();
		_img = IMAGEMANAGER->findImage(imageName);
	}
}

void state::col()
{
	RECT temp;
	RECT PRC = _p->getRect();
	// 잡기 상태
	for (int i = 0; i < _vem.size(); i++)
	{
		RECT ERC = _vem[i]->getSRc();

		if (IntersectRect(&temp, &PRC, &ERC))
		{
			_p->setState(new grab);
		}
	}
}


