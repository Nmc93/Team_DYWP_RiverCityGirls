#include "pch.h"
#include "wBatJump.h"
#include "player.h"

HRESULT wBatJump::init()
{
    return S_OK;
}

void wBatJump::release()
{
}

void wBatJump::update()
{
    state::update();

    findImage("P_WBATJUMP");
}

void wBatJump::render()
{
    state::render();
}

void wBatJump::stateChange()
{
	if (_p->getJumpPower() < 0 && !_p->getIsJump())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
			KEYMANAGER->isStayKeyDown(VK_RIGHT) ||
			KEYMANAGER->isStayKeyDown(VK_UP) ||
			KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_p->getSpeed() == 5.0f) _p->setState(new wBatWalk);
			else if (_p->getSpeed() == 10.0f) _p->setState(new wBatRun);
		}
		else
		{
			_motion->stop();
			_p->setState(new wBatIdle);
		}
	}
}

void wBatJump::setAni()
{
	if (_p->getSpeed() == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
			KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_p->setSpeed(5.0f);
		}
	}

	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATJUMP");
	else _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATJUMP");
}
