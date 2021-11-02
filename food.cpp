#include "pch.h"
#include "food.h"


food::food()
{
}


food::~food()
{
}


HRESULT food::init(FOODSTATE st, POINT ptxy)
{

    state = st;

    if (state == APPLE)
    {
        img = new image;
        img->init("image/object/apple.bmp", 100, 100, 1, 1, true, RGB(255, 0, 255));

    }

    else if (state == CHILI)
    {
        img = new image;
        img->init("image/object/chili.bmp", 100, 100, 1, 1, true, RGB(255, 0, 255));

    }

    else if (state == HEN)
    {
        img = new image;
        img->init("image/object/hen.bmp", 100, 100, 1, 1, true, RGB(255, 0, 255));

    }

    _sX = ptxy.x;
    _sY = ptxy.y;

    x = _sX;
    y = _sY - img->getFrameHeight() / 2;

    RC = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

    _isJump = true;
    _gravity = 0.5f;
    _jumpPower = 5;

    return S_OK;
}

void food::release()
{
}

void food::update()
{

    RC = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

    drop();

    //µîÀå Á¡ÇÁ
    if (_isJump)
    {
        y -= _jumpPower;
        _jumpPower -= _gravity;
    }
    else
    {
        x = _sX;
        y = _sY - img->getFrameHeight() / 2;
        _jumpPower = 0;

    }

    //¸ØÃç¾ß ÇÏ´Â ÁÂÇ¥ Á¶°Ç
    if (RC.bottom > _sY)
    {
        _jumpPower = 0;

        _isJump = false;
    }
}

void food::drop()
{


}

void food::render()
{
    img->frameRender(getMemDC(), RC.left, RC.top);

}
