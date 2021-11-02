#include "pch.h"
#include "sAttack.h"
#include "player.h"

HRESULT sAttack::init()
{
    return S_OK;
}

void sAttack::release()
{
}

void sAttack::update()
{
    state::update();

	findImage("P_SATTACK");

	if (_motion->getNowPlayIdx() == _img->getMaxFrameX() / 2) _p->setAtk(true);
	else _p->setAtk(false);

	if (_wDir == LEFT) _p->setAtkBox(RectMake(_p->getHitBox().left - 70, _p->getY() - _p->getImage()->getFrameHeight() / 5, 80, 60));
	else  _p->setAtkBox(RectMake(_p->getHitBox().right - 10, _p->getY() - _p->getImage()->getFrameHeight() / 5, 80, 60));
	
}

void sAttack::render()
{
    state::render();
}

void sAttack::stateChange()
{

}

void sAttack::setAni()
{
	_p->setSpeed(0.0f);

	_p->setAtk(true);
	_p->setType(PSTRONGATK);

	if (_motion == NULL)
	{
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_SATTACK");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_SATTACK");
	}
	
	
}

