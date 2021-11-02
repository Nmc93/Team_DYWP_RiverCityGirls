#include "pch.h"
#include "run.h"
#include "player.h"

HRESULT run::init()
{
	return S_OK;
}

void run::release()
{
}

void run::update()
{
	state::update();
	if (!_motion->isPlay()) _motion->start();


	findImage("P_RUN");
	_p->setAtk(false);


	_p->setAtkBox(RectMakeCenter(_p->getX(), _p->getY(), 1, 1));
}

void run::render()
{
	state::render();
}

void run::stateChange()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_p->setJumpPower(15.0f);
		_p->setState(new jump);
	}
	else if (KEYMANAGER->isOnceKeyDown('X')) _p->setState(new atk);
	else if (KEYMANAGER->isOnceKeyDown('C')) _p->setState(new sAttack);
	else if (KEYMANAGER->isOnceKeyDown('V')) _p->setState(new dashAttack);
	else if (KEYMANAGER->isOnceKeyDown('F')) _p->setState(new guard);


	// 아무것도 안누르고 있으면
	if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_UP) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_p->setState(new idle);
	}
}

void run::setAni()
{
	_p->setSpeed(10.0f);

	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_RUN");
	else  _motion = KEYANIMANAGER->findAnimation("RIGHT_RUN");
	
}