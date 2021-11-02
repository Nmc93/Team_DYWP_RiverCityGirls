#include "pch.h"
#include "guard.h"
#include "player.h"

HRESULT guard::init()
{
	return S_OK;
}

void guard::release()
{
}

void guard::update()
{
	state::update();

	findImage("P_GUARD");

}

void guard::render()
{
	state::render();
}

void guard::stateChange()
{
	if (KEYMANAGER->isOnceKeyUp('F')) _p->cbState(_p);
}

void guard::setAni()
{
	_p->setSpeed(0);

	// 딱 한번만 실행 (방향이 바뀌어도 같아야 하므로)
	if (_motion == NULL) {
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_GUARD");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_GUARD");
	}
}
