#include "pch.h"
#include "wBatThrow.h"

HRESULT wBatThrow::init()
{
	return S_OK;
}

void wBatThrow::release()
{
}

void wBatThrow::update()
{
	state::update();

	findImage("P_WBATTHROW");
}

void wBatThrow::render()
{
	state::render();
}

void wBatThrow::stateChange()
{
}

void wBatThrow::setAni()
{
	if (_motion == NULL)
	{
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATTHROW");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATTHROW");
	}
}
