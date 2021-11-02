#include "pch.h"
#include "dead.h"

HRESULT dead::init()
{
	return S_OK;
}

void dead::release()
{
}

void dead::update()
{
	state::update();

	findImage("P_DEAD");
}

void dead::render()
{
	state::render();
}

void dead::stateChange()
{

}

void dead::setAni()
{	
	if (_motion == NULL)
	{
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_DEAD");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_DEAD");
	}
}
