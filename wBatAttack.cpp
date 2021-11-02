#include "pch.h"
#include "wBatAttack.h"
#include "player.h"

HRESULT wBatAttack::init()
{
	return S_OK;
}

void wBatAttack::release()
{
}

void wBatAttack::update()
{
	state::update();

	findImage("P_WBATATTACK");
}

void wBatAttack::render()
{
	state::render();
}

void wBatAttack::stateChange()
{

}

void wBatAttack::setAni()
{
	_p->setSpeed(0);

	if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATATTACK");
	else _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATATTACK");
}
