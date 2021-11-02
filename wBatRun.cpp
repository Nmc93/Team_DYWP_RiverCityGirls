#include "pch.h"
#include "wBatRun.h"
#include "player.h"

HRESULT wBatRun::init()
{
    return S_OK;
}

void wBatRun::release()
{
}

void wBatRun::update()
{
    state::update();
    if (!_motion->isPlay()) _motion->start();

    findImage("P_WBATRUN");

}

void wBatRun::render()
{
    state::render();
}

void wBatRun::stateChange()
{
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        _p->setJumpPower(20.0f);
        _p->setState(new wBatJump);
    }
    else if (KEYMANAGER->isOnceKeyDown('A')) _p->setState(new wBatAttack);
    else if (KEYMANAGER->isOnceKeyDown('S')) _p->setState(new wBatThrow);


    // 아무것도 안누르고 있으면
    if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
        !KEYMANAGER->isStayKeyDown(VK_LEFT) &&
        !KEYMANAGER->isStayKeyDown(VK_UP) &&
        !KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _p->setState(new wBatIdle);
    }
}

void wBatRun::setAni()
{
    _p->setSpeed(10.0f);

    if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_WBATRUN");
    else  _motion = KEYANIMANAGER->findAnimation("RIGHT_WBATRUN");
}
