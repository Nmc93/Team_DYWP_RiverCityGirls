#include "pch.h"
#include "wallJump.h"

HRESULT wallJump::init()
{

    return S_OK;
}

void wallJump::release()
{

}

void wallJump::update()
{
    state::update();



}

void wallJump::render()
{
    state::render();
}

void wallJump::stateChange()
{
    
}

void wallJump::setAni()
{

}
