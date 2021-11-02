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

	// �� �ѹ��� ���� (������ �ٲ� ���ƾ� �ϹǷ�)
	if (_motion == NULL) {
		if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_GUARD");
		else _motion = KEYANIMANAGER->findAnimation("RIGHT_GUARD");
	}
}
