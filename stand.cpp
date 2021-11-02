#include "pch.h"
#include "stand.h"
#include "player.h"

HRESULT stand::init()
{
    return S_OK;
}

void stand::release()
{
}

void stand::update()
{
    state::update();

    findImage("P_STAND");

}

void stand::render()
{
    state::render();
}

void stand::stateChange()
{

}

void stand::setAni()
{
    if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_STAND");
    else _motion = KEYANIMANAGER->findAnimation("RIGHT_STAND");
}
