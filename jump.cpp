#include "pch.h"
#include "jump.h"
#include "player.h"

HRESULT jump::init()
{
	return S_OK;
}

void jump::release()
{
}

void jump::update()
{
	state::update();

	findImage("P_JUMP");

	_p->setAtkBox(RectMakeCenter(_p->getX(), _p->getY(), 1, 1));
}

void jump::render()
{
	state::render();
}

void jump::stateChange()
{
	if (_p->getJumpPower() < 0 && !_p->getIsJump())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)  ||
			KEYMANAGER->isStayKeyDown(VK_RIGHT) ||
			KEYMANAGER->isStayKeyDown(VK_UP)	||
			KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_p->getSpeed() == 5.0f) _p->setState(new walk);
			else if (_p->getSpeed() == 10.0f) _p->setState(new run);
		}
		else
		{
			_motion->stop();
			_p->setState(new idle);
		}
	}

	//else if (KEYMANAGER->isOnceKeyDown('X'))	  _k->setState(new atk);

}

void jump::setAni()
{
	if (_p->getSpeed() == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
			KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setSpeed(5.0f);
		}
	}

	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_JUMP");
	else _motion = KEYANIMANAGER->findAnimation("RIGHT_JUMP");
	
}