#include "pch.h"
#include "grab.h"
#include "player.h"

HRESULT grab::init()
{
    return S_OK;
}

void grab::release()
{
}

void grab::update()
{
    state::update();
    _timer++;

    findImage("P_GRAB");
}

void grab::render()
{
    state::render();
}

void grab::stateChange()
{
    if (100 < _timer) _p->setState(new idle);

    if (KEYMANAGER->isOnceKeyDown('B')) _p->setState(new grabFail);
}

void grab::setAni()
{
    _p->setSpeed(0);

    if (_motion == NULL)
    {
        if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_GRAB");
        else _motion = KEYANIMANAGER->findAnimation("RIGHT_GRAB");
    }
}
