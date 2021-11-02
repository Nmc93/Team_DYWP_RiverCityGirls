#include "pch.h"
#include "dashAttack.h"
#include "player.h"

HRESULT dashAttack::init()
{
	return S_OK;
}

void dashAttack::release()
{
}

void dashAttack::update()
{
	state::update();
	
	findImage("P_DASHATTACK");

	if (_motion->getNowPlayIdx() == _img->getMaxFrameX() / 2) _p->setAtk(true);
	else _p->setAtk(false);

	if (_wDir == LEFT) _p->setAtkBox(RectMake(_p->getHitBox().left - 40, _p->getY() - _p->getImage()->getFrameHeight() / 6, 50, 60));
	else  _p->setAtkBox(RectMake(_p->getHitBox().right - 10, _p->getY() - _p->getImage()->getFrameHeight() / 6, 50, 60));
}

void dashAttack::render()
{
	state::render();
}

void dashAttack::stateChange()
{

}

void dashAttack::setAni()
{
	_p->setSpeed(8.0f);

	_p->setAtk(true);
	_p->setType(PSTRONGATK);

	if (_motion == NULL) 
	{
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_DASHATTACK");
		else  _motion = KEYANIMANAGER->findAnimation("RIGHT_DASHATTACK");
	}
	
}
