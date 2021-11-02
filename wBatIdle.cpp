#include "pch.h"
#include "wBatIdle.h"
#include "player.h"

HRESULT wBatIdle::init()
{
    return S_OK;
}

void wBatIdle::release()
{
}

void wBatIdle::update()
{
    state::update();

    findImage("P_WBATIDLE");

}

void wBatIdle::render()
{
    state::render();
}

void wBatIdle::stateChange()
{
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        _p->setJumpPower(20.0f);
        _p->setState(new wBatJump);
    }
    else if (KEYMANAGER->isOnceKeyDown('A')) _p->setState(new wBatAttack);
    else if (KEYMANAGER->isOnceKeyDown('S')) _p->setState(new wBatThrow);


    if (KEYMANAGER->isOnceKeyDown(VK_LEFT) ||
        KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
        KEYMANAGER->isOnceKeyDown(VK_UP) ||
        KEYMANAGER->isOnceKeyDown(VK_DOWN))
    {
        _p->setState(new wBatWalk);
    }
}

void wBatIdle::setAni()
{
    _p->setSpeed(0.0f);

    if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATIDLE");
    else _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATIDLE");
}
