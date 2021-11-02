#include "pch.h"
#include "atk.h"
#include "player.h"

HRESULT atk::init()
{
    return S_OK;
}

void atk::release()
{
}

void atk::update()
{
	state::update();
	cbFunction();

	if (KEYMANAGER->isOnceKeyDown('X') && _atkCount < 2)
	{
		if (_motion->getNowPlayIdx() >= _img->getMaxFrameX() - 2)
		{
			_motion->stop();
			_atkCount++;
			
			_p->setType(PNORMALATK);
		}
	}
	if(_atkCount == 0) _p->setType(PNORMALATK);
	if (_atkCount == 2) _p->setType(PSTRONGATK);

	switch(_atkCount)
	{
		case 0:
			_img = IMAGEMANAGER->findImage("P_COMBOATTACK1");
		break;

		case 1:
			_img = IMAGEMANAGER->findImage("P_COMBOATTACK2");
		break;

		case 2:
			_img = IMAGEMANAGER->findImage("P_COMBOATTACK3");
		break;
	}

	if (_motion->getNowPlayIdx() == _img->getMaxFrameX() / 2) _p->setAtk(true);
	else _p->setAtk(false);


	if (_wDir == LEFT) _p->setAtkBox(RectMake(_p->getHitBox().left - 70, _p->getY() - _p->getImage()->getFrameHeight() / 5, 80, 60));
	else  _p->setAtkBox(RectMake(_p->getHitBox().right - 10, _p->getY() - _p->getImage()->getFrameHeight() / 5, 80, 60));

	if (_motion->getNowPlayIdx() == _img->getMaxFrameX() / 2) _p->setAtk(true);
	if (_motion->getNowPlayIdx() == (_img->getMaxFrameX() / 2) + 1) _p->setAtk(false);
}

void atk::render()
{
    state::render();
}

void atk::stateChange()
{
}

void atk::setAni()
{
	_p->setSpeed(0);

	if (_wDir == LEFT)
	{
		switch (_atkCount)
		{
		case 0:
			_motion = KEYANIMANAGER->findAnimation("LEFT_COMBOATTACK1");
			break;

		case 1:
			_motion = KEYANIMANAGER->findAnimation("LEFT_COMBOATTACK2");
			break;

		case 2:
			_motion = KEYANIMANAGER->findAnimation("LEFT_COMBOATTACK3");
			break;
		}
	}
	else if (_wDir == RIGHT)
	{
		switch (_atkCount)
		{
		case 0:
			_motion = KEYANIMANAGER->findAnimation("RIGHT_COMBOATTACK1");
			break;

		case 1:
			_motion = KEYANIMANAGER->findAnimation("RIGHT_COMBOATTACK2");
			break;

		case 2:
			_motion = KEYANIMANAGER->findAnimation("RIGHT_COMBOATTACK3");
			break;
		}
	}

	_motion->resume();
}

void atk::cbFunction()
{
	if (!_motion->isPlay())
	{
		_motion->stop();
		_p->setState(new idle);
		_p->update();				// ¿òÁ÷¿©¼­ ³Ö¾îÁÜ
	}
}


 