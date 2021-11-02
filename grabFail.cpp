#include "pch.h"
#include "grabFail.h"

HRESULT grabFail::init()
{
	return S_OK;
}

void grabFail::release()
{
}

void grabFail::update()
{
	state::update();

	findImage("P_GRABFAIL");
}

void grabFail::render()
{
	state::render();
}

void grabFail::stateChange()
{

}

void grabFail::setAni()
{
	if (_motion == NULL)
	{
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_GRABFAIL");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_GRABFAIL");
	}
}
