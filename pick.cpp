#include "pch.h"
#include "pick.h"
#include "player.h"

HRESULT pick::init()
{
    return S_OK;
}

void pick::release()
{
}

void pick::update()
{
    state::update();

    findImage("P_PICK");
}

void pick::render()
{
    state::render();
}

void pick::stateChange()
{

}

void pick::setAni()
{
    if (_motion == NULL)
    {
        if (_wDir == LEFT) _motion = KEYANIMANAGER->findAnimation("LEFT_PICK");
        else _motion = KEYANIMANAGER->findAnimation("RIGHT_PICK");
    }
}

