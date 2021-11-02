#include "pch.h"
#include "idle.h"
#include "player.h"
#include "enemy.h"

HRESULT idle::init()
{
    state::init();

	// 처음 시작이라서 걍 초기화 해줌

	_img = IMAGEMANAGER->findImage("P_IDLE");
	_motion = KEYANIMANAGER->findAnimation("LEFT_IDLE");
	_motion->start();

    return S_OK;
}

void idle::release()
{
}

void idle::update()
{
	state::update();

	findImage("P_IDLE");

	_p->setAtk(false);
	//_p->setIsHit(false);

	for (int i = 0; i < _vem.size(); i++)
	{
		if (_vem[i]->getAType() == EIDLE)
		{
			_p->setIsHit(false);
		}
	}


	_p->setAtkBox(RectMakeCenter(_p->getX(), _p->getY(), 1, 1));
}

void idle::render()
{
	state::render();

	int a = _vem.size();
	char str[128];
	sprintf_s(str, "asdf: %d", a);
	TextOut(getMemDC(), 0, 150, str, strlen(str));
}

void idle::stateChange()
{
	
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) ||
		KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyDown(VK_UP) ||
		KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_p->setState(new walk);
	}

	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_p->setJumpPower(15.0f);
		_p->setState(new jump);
	}

	else if (KEYMANAGER->isOnceKeyDown('X')) _p->setState(new atk);
	else if (KEYMANAGER->isOnceKeyDown('C')) _p->setState(new sAttack);
	else if (KEYMANAGER->isOnceKeyDown('F')) _p->setState(new guard);

}

void idle::setAni()
{
	_p->setSpeed(0.0f);
	
	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_IDLE");
	else _motion = KEYANIMANAGER->findAnimation("RIGHT_IDLE");
}
