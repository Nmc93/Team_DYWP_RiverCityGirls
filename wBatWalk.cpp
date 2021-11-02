#include "pch.h"
#include "wBatWalk.h"
#include "player.h"

HRESULT wBatWalk::init()
{
	return S_OK;
}

void wBatWalk::release()
{
}

void wBatWalk::update()
{
	state::update();
	if (!_motion->isPlay()) _motion->start();

	findImage("P_WBATWALK");
	_timer++;
}

void wBatWalk::render()
{
	state::render();
}

void wBatWalk::stateChange()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_p->setJumpPower(20.0f);
		_p->setState(new wBatJump);
	}
	else if (KEYMANAGER->isOnceKeyDown('A')) _p->setState(new wBatAttack);
	else if (KEYMANAGER->isOnceKeyDown('S')) _p->setState(new wBatThrow);

	// RUN 변환
	if (2 < _timer && _timer <= 10) {
		// 그 안에 뭐라도 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
			KEYMANAGER->isOnceKeyDown(VK_LEFT)  ||
			KEYMANAGER->isOnceKeyDown(VK_UP)  ||
			KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_p->setState(new wBatRun);
		}
	}
	else
	{
		// 아무것도 안누르고 있으면
		if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
			!KEYMANAGER->isStayKeyDown(VK_LEFT)  &&
			!KEYMANAGER->isStayKeyDown(VK_UP)    &&
			!KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_p->setState(new wBatIdle);
		}
	}
	
}

void wBatWalk::setAni()
{
	_p->setSpeed(5.0f);

	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATWALK");
	else if (_wDir == RIGHT) _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATWALK");
}
