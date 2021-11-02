#include "pch.h"
#include "walk.h"
#include "player.h"
#include "enemy.h"

HRESULT walk::init()
{

	return S_OK;
}

void walk::release()
{
}

void walk::update()
{
	state::update();
	if (!_motion->isPlay()) _motion->start();

	findImage("P_WALK");
	_timer++;

	_p->setAtk(false);

	_p->setAtkBox(RectMakeCenter(_p->getX(), _p->getY(), 1, 1));
}

void walk::render()
{
	state::render();

	char str[128];
	sprintf_s(str, "시간 : %d", _timer);
	TextOut(getMemDC(), 10, 60, str, strlen(str));

}

void walk::stateChange()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_p->setJumpPower(15.0f);
		_p->setState(new jump);
	}
	else if (KEYMANAGER->isOnceKeyDown('X')) _p->setState(new atk);
	else if (KEYMANAGER->isOnceKeyDown('C')) _p->setState(new sAttack);
	else if (KEYMANAGER->isOnceKeyDown('F')) _p->setState(new guard);

	// RUN 변환
	if (2 < _timer && _timer <= 10) {
		// 그 안에 뭐라도 누르면
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
			KEYMANAGER->isOnceKeyDown(VK_LEFT)  ||
			KEYMANAGER->isOnceKeyDown(VK_UP)  ||
			KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_p->setState(new run);
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
			_p->setState(new idle);
		}
	}
	
	

}

void walk::setAni()
{
	_p->setSpeed(5.0f);
	
	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WALK");
	else if (_wDir == RIGHT) _motion = KEYANIMANAGER->findAnimation("RIGHT_WALK");
}
