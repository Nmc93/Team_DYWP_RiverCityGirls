#include "pch.h"
#include "bat.h"
#include <random>


bat::bat()
{
}


bat::~bat()
{
}



HRESULT bat::init(POINT ptxy)
{
    
    _idle = new image;
    _idle->init("image/object/bat.bmp", 179, 104, 1, 2, true, RGB(255, 0, 255));

    _batImage = _idle;

    _sX = ptxy.x;
    _sY = ptxy.y;

    x = _sX;
    y = _sY - _batImage->getFrameHeight() / 2;


    _batRC = RectMakeCenter(x, y, _batImage->getFrameWidth(), _batImage->getFrameHeight());

    _isJump = true;
    _gravity = 0.5f;
    _jumpPower = 5;

    _isGo = false;
    count++;

    goBat(WEAPONSTATE::LEFT_IDLE, {});

    return S_OK;
}

void bat::release()
{
}

void bat::update()
{
    _batRC = RectMakeCenter(x, y, _batImage->getFrameWidth(), _batImage->getFrameHeight());

    drop();

    goBat(WEAPONSTATE ::LEFT_IDLE , {});
}



void bat::drop()
{
    
    //무기의 등장 쩜푸
    if (_isJump)
    {
        y -= _jumpPower;
        _jumpPower -= _gravity;
    }
    else
    {
        x = _sX;
        y = _sY - _batImage->getFrameHeight() / 2;
        _jumpPower = 0;

    }

    //무기가 멈춰야 하는 좌표 조건
    if (_batRC.bottom > _sY)
    {
        _jumpPower = 0;

        _isJump = false;
    }
    
}

void bat::goBat(WEAPONSTATE st, POINT ptxy)
{   /*
    //무기가 날아가는 느낌
    if (KEYMANAGER->isOnceKeyDown('L'))
    {
        if (_isGo == true)
        {

            _batImage = _idle;
            WEAPONSTATE::RIGHT_IDLE;
            _batImage->setFrameY(1);

            _sX = x;
            _sY = y;

            x = _sX += 5;
            y = _sY;

            _batRC = RectMakeCenter(x, y, _batImage->getFrameWidth(), _batImage->getFrameHeight());

          

        }
        
        if (_batRC.left <= 0)
        {
            _batImage = _idle;
            WEAPONSTATE::LEFT_IDLE;
            _batImage->setFrameY(0);

            _sX = x;
            _sY = y;

            x = _sX += 5;
            y = _sY;

            _batRC = RectMakeCenter(x, y, _batImage->getFrameWidth(), _batImage->getFrameHeight());

            _isGo = true;

        }

        else if (_isJump == false)
        {

            _batRC.right <= WINSIZEX;
        }
         
    }*/
}


void bat::render()
{

    //bat 크기 모양 보여주는 렉트
    //Rectangle(getMemDC(), _batRC);

    _batImage->frameRender(getMemDC(), _batRC.left, _batRC.top);

}