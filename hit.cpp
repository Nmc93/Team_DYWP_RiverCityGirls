#include "pch.h"
#include "hit.h"
#include "player.h"

HRESULT hit::init()
{

	return S_OK;
}

void hit::release()
{
}

void hit::update()
{
	state::update();

	findImage("P_HIT");

	// »ìÂ¦ µÚ·Î
	if (_p->getEnemyDir() == LEFT) _p->setSX(_p->getSX() + 1);
	else _p->setSX(_p->getSX() - 1);

	_p->setIsHit(true);

}

void hit::render()
{
	state::render();
}

void hit::stateChange()
{

}

void hit::setAni()
{

	if (_motion == NULL)
	{
		if (_p->getEnemyDir() == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_HIT");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_HIT");
	}
}
