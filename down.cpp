#include "pch.h"
#include "down.h"
#include "player.h"

HRESULT down::init()
{
	return S_OK;
}

void down::release()
{
}

void down::update()
{

	state::update();
		

	findImage("P_DOWN");

	_timer++;


	_p->setIsHit(true);
	// »ìÂ¦ µÚ·Î
	
	if (_p->getEnemyDir() == LEFT && _motion->getNowPlayIdx() < _img->getMaxFrameX()) _p->setSX(_p->getSX() + 1);
	else if(_p->getEnemyDir() == RIGHT && _motion->getNowPlayIdx() < _img->getMaxFrameX() - 1) _p->setSX(_p->getSX() - 1);

}

void down::render()
{
	state::render();
}

void down::stateChange()
{
	if (_timer > 200) _p->setState(new stand);
}

void down::setAni()
{
	if (_p->getEnemyDir() == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_DOWN");
	else _motion = KEYANIMANAGER->findAnimation("RIGHT_DOWN");
}
