#include "pch.h"
#include "player.h"
#include "enemy.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	playerImage();
	playerAni();

	// 처음 상태
	_state = new idle;
	_state->init();

	// 초기화
	_img = _state->getImage();
	_shadowImg = IMAGEMANAGER->findImage("SHADOW1");

	_sx = WINSIZEX / 2;
	_sy = WINSIZEY - 100;
	_shadowRc = RectMakeCenter(_sx, _sy, _shadowImg->getWidth(), _shadowImg->getHeight());

	_x = _sx;
	_y = _sy - (float)_img->getFrameHeight() / 2;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	
	_speed = 0;
	_jumpPower = 10;

	_isJump = false;

	_ox = WINSIZEX - 100;
	_oy = WINSIZEY - 100;

	// 픽셀충돌
	_pc = new pixelCol;
	_pc->init(_shadowRc);
	_pc->setCamera(_cam);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 상태 전달
	_state->setKnight(this);
	
	move();
	collision();

	_pc->update(_shadowRc);

	_state->update();
	_img = _state->getImage();
}

void player::render()
{	
	//_shadowImg->render(getMemDC(), _shadowRc.left, _shadowRc.top);
	//_state->render();

	// 방망이 줍기
	//if(!_isGain) Rectangle(getMemDC(), _orc);

	if (KEYMANAGER->isToggleKey(VK_NUMPAD0))
	{
		char str[128];
		sprintf_s(str, " _isJump : %d", _isJump);
		TextOut(getMemDC(), 0, 200, str, strlen(str));

		sprintf_s(str, " _rc.bottom : %f", (float)_rc.bottom);
		TextOut(getMemDC(), 0, 220, str, strlen(str));

		sprintf_s(str, " _sy : %d", _sy);
		TextOut(getMemDC(), 0, 240, str, strlen(str));

		sprintf_s(str, " _ssx : %d", _sx);
		TextOut(getMemDC(), 0, 260, str, strlen(str));

		sprintf_s(str, " _y : %.2f", _y);
		TextOut(getMemDC(), 0, 280, str, strlen(str));

		sprintf_s(str, " _timer : %d", _timer);
		TextOut(getMemDC(), 0, 300, str, strlen(str));

		sprintf_s(str, " _isMove111 : %d", _pc->getIsMove());
		TextOut(getMemDC(), 0, 600, str, strlen(str));

		// 아니아니
		sprintf_s(str, " _isAtk : %d", _isAtk);
		TextOut(getMemDC(), 50, 620, str, strlen(str));

		sprintf_s(str, " _atkType : %d", _atkType);
		TextOut(getMemDC(), 50, 640, str, strlen(str));

		sprintf_s(str, " _isHit : %d", _isHit);
		TextOut(getMemDC(), 50, 660, str, strlen(str));
	}

	_pc->render();
	if (KEYMANAGER->isToggleKey(VK_F11))
	{
		Rectangle(getMemDC(), _hitBox);
		Rectangle(getMemDC(), _atkBox);
	}
}

void player::stateRender(animation* motion)
{
	_img->aniRender(getMemDC(), _rc.left,_rc.top, motion);
}

void player::move()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_wDir = LEFT; _hDir = NORMAL;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_wDir = RIGHT; _hDir = NORMAL;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))		_hDir = UP;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))		_hDir = DOWN;
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))	_isJump = true;

	// 움직임
	if (!_isJump)
	{
		// 위 아래만 누를 경우
		if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_hDir == UP && _rc.top > 0 && _pc->getIsMove()) _sy -= _speed;
			if (_hDir == DOWN && _shadowRc.bottom < WINSIZEY && _pc->getIsMove()) _sy += _speed;
		}
		else
		{
			if (_wDir == LEFT && _pc->getIsMove())
			{
				if (_sx < 200 && _cam->getX() > 10 && !_isCameraLock) _cam->setX(_cam->getX() - _speed);
				else
				{
					if (_shadowRc.left > 0 ) _sx -= _speed;
				}

			}
			else if (_wDir == RIGHT)
			{
				if (_sx > 400 && _cam->getX() < _bImg->getWidth() - WINSIZEX - 10 && !_isCameraLock)
																				_cam->setX(_cam->getX() + _speed);
				else
				{
					if (_shadowRc.right < WINSIZEX && _pc->getIsMove()) _sx += _speed;
				}
			}

			if (_hDir == UP && _rc.top > 0 && _pc->getIsMove()) _sy -= _speed;
			if (_hDir == DOWN && _shadowRc.bottom < WINSIZEY && _pc->getIsMove()) _sy += _speed;
		}

		// 쉐도우
		_x = _sx;
		_y = _sy - _img->getFrameHeight() / 2;
	}
	else
	{
		// 움직임
		if (_rc.bottom <= _sy)
		{
			_x = _sx;
			_y -= _jumpPower;
			_jumpPower -= GRAVITY;
		}
		else
		{
			_y = _sy - _img->getFrameHeight() / 2;
			_isJump = false;
		}

		
		if (_hDir == NORMAL)
		{
			if (_wDir == LEFT)
			{
				if (_sx < 200 && _cam->getX() > 10 && !_isCameraLock) _cam->setX(_cam->getX() - _speed);
				else
				{
					if (_shadowRc.left > 0) _sx -= _speed;
				}
			}
			else if (_wDir == RIGHT)
			{
				if (_sx > 800 && _cam->getX() < IMAGEMANAGER->findImage("BACKGROUND")->getWidth() - WINSIZEX - 10 && !_isCameraLock) _cam->setX(_cam->getX() + _speed);
				else
				{
					if (_shadowRc.right < WINSIZEX) _sx += _speed;
				}
			}
		}
		else
		{
			if (_hDir == UP)
			{
				if (_shadowRc.top > 0)
				{
					_sy -= _speed;
					_y -= _speed;
				}
			}
			else if (_hDir == DOWN)
			{
				if (_shadowRc.bottom < WINSIZEY)
				{
					_sy += _speed;
					_y += _speed;
				}
			}
		}

	}

	// 렉트들
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_shadowRc = RectMakeCenter(_sx, _sy, _shadowImg->getWidth(), _shadowImg->getHeight());

	_hitBox = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("P_IDLE")->getFrameWidth(), IMAGEMANAGER->findImage("P_IDLE")->getFrameHeight());
}

void player::collision()
{
	
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		setState(new hit);
	}

	// HP가 다 닳게 되면
	if (KEYMANAGER->isOnceKeyDown('M')) setState(new down);
	

	// 방망이 줍는 거
	RECT temp;
	if (IntersectRect(&temp, &_shadowRc, &_orc) && !_isGain)
	{
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			_isGain = true;
			setState(new pick);
		}
	}

	_orc = RectMakeCenter(_ox - _cam->getX(), _oy, 50, 50);
}

void player::playerImage()
{
	IMAGEMANAGER->addImage("SHADOW1", "shadow.bmp", 128, 39, true, RGB(255, 0, 255));
	/*
	IMAGEMANAGER->addFrameImage("P_IDLE", "image/character/player/idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WALK", "image/character/player/walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_RUN", "image/character/player/run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_JUMP", "image/character/player/jump.bmp", 480, 680, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK1", "image/character/player/comboAttack1.bmp", 1548, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK2", "image/character/player/comboAttack2.bmp", 1869, 402, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK3", "image/character/player/comboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_SATTACK", "image/character/player/strongAttack.bmp", 3030, 474, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DOWN", "image/character/player/down.bmp", 4968, 390, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_STAND", "image/character/player/stand.bmp", 1863, 450, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DASHATTACK", "image/character/player/dashAttack.bmp", 2565, 414, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GUARD", "image/character/player/guard.bmp", 351, 378, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DEAD", "image/character/player/dead.bmp", 7280, 478, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GRAB", "image/character/player/grab.bmp", 270, 384, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GRABFAIL", "image/character/player/grabFail.bmp", 812, 422, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_PICK", "image/character/player/pick.bmp", 222, 450, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_HIT", "image/character/player/hit.bmp", 246, 420, 2, 2, true, RGB(255, 0, 255));

	// 방망이 상태
	IMAGEMANAGER->addFrameImage("P_WBATIDLE", "image/character/player/wBatIdle.bmp", 1440, 560, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATWALK", "image/character/player/wBatWalk.bmp", 1476, 500, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATRUN", "image/character/player/wBatRun.bmp", 6784, 560, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATJUMP", "image/character/player/wBatJump.bmp", 480, 680, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATATTACK", "image/character/player/wBatAttack.bmp", 1700, 700, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATTHROW", "image/character/player/wBatThrow.bmp", 1616, 600, 8, 2, true, RGB(255, 0, 255));


	//====================================================================================================================================

	IMAGEMANAGER->addFrameImage("P_CLIMB", "image/character/player/climb.bmp", 720, 237, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_CLIMBTOP", "image/character/player/climbTop.bmp", 288, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_CLIMBDOWN", "image/character/player/climbDown.bmp", 288, 234, 3, 1, true, RGB(255, 0, 255));	
	*/
}

void player::playerAni()
{
	
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_IDLE", "P_IDLE", 11, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_IDLE", "P_IDLE", 12, 23, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WALK", "P_WALK", 11, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WALK", "P_WALK", 12, 23, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_RUN", "P_RUN", 15, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_RUN", "P_RUN", 16, 31, 10, false, true);
	int leftJump[] = {0, 1, 2, 1, 0};
	KEYANIMANAGER->addArrayFrameAnimation("LEFT_JUMP", "P_JUMP", leftJump, 5, 7, false);
	int rightJump[] = {5, 4, 3, 4, 5};
	KEYANIMANAGER->addArrayFrameAnimation("RIGHT_JUMP", "P_JUMP", rightJump, 5, 7, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_COMBOATTACK1", "P_COMBOATTACK1", 5, 0, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_COMBOATTACK1", "P_COMBOATTACK1", 6, 11, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_COMBOATTACK2", "P_COMBOATTACK2", 6, 0, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_COMBOATTACK2", "P_COMBOATTACK2", 7, 13, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_COMBOATTACK3", "P_COMBOATTACK3", 8, 0, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_COMBOATTACK3", "P_COMBOATTACK3", 9, 17, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_SATTACK", "P_SATTACK", 9, 0, 10, false, false, cbState, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_SATTACK", "P_SATTACK", 10, 19, 10, false, false, cbState, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_DOWN", "P_DOWN", 0, 22, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_DOWN", "P_DOWN", 45, 23, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_STAND", "P_STAND", 0, 8, 10, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_STAND", "P_STAND", 17, 9, 10, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_DASHATTACK", "P_DASHATTACK", 7, 0, 10, false, false, cbWalk, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_DASHATTACK", "P_DASHATTACK", 8, 15, 10, false, false, cbWalk, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_GUARD", "P_GUARD", 0, 2, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_GUARD", "P_GUARD", 5, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_DEAD", "P_DEAD", 0, 25, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_DEAD", "P_DEAD", 49, 26, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_GRAB", "P_GRAB", 0, 1, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_GRAB", "P_GRAB", 3, 2, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_GRABFAIL", "P_GRABFAIL", 0, 3, 7, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_GRABFAIL", "P_GRABFAIL", 7, 4, 7, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_PICK", "P_PICK", 0, 1, 5, false, false, cbBatIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_PICK", "P_PICK", 3, 2, 5, false, false, cbBatIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_HIT", "P_HIT", 0, 1, 7, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_HIT", "P_HIT", 2, 3, 7, false, false, cbIdle, this);

	// 방망치 상태
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WBATIDLE", "P_WBATIDLE", 11, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WBATIDLE", "P_WBATIDLE", 12, 23, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WBATWALK", "P_WBATWALK", 11, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WBATWALK", "P_WBATWALK", 12, 23, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WBATRUN", "P_WBATRUN", 15, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WBATRUN", "P_WBATRUN", 16, 31, 10, false, true);
	int leftBatJump[] = { 0, 1, 2, 1, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("LEFT_WBATJUMP", "P_WBATJUMP", leftBatJump, 5, 9, true);
	int rightBatJump[] = { 5, 4, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("RIGHT_WBATJUMP", "P_WBATJUMP", rightBatJump, 5, 9, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WBATATTACK", "P_WBATATTACK", 4, 0, 10, false, false, cbState, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WBATATTACK", "P_WBATATTACK", 5, 9, 10, false, false, cbState, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("LEFT_WBATTHROW", "P_WBATTHROW", 7, 0, 10, false, false, cbIdle, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("RIGHT_WBATTHROW", "P_WBATTHROW", 8, 15, 10, false, false, cbIdle, this);
	
}

void player::playerHit(player* p, vector<enemy*> e, int distance)
{

	RECT temp;
	RECT PRC = p->getHitBox();
	
	for (int i = 0; i < e.size(); i++)
	{
		// 처음 충돌에 필요한 것들 셋팅 셋팅!!
		RECT ERC = e[i]->getAtkBox();
		bool isAtk = e[i]->getAttAck();

		int atkType = e[i]->getAttNum();
		//int atkType = 2;

		if (!_isHit)
		{
			// 플레이어가 왼쪽
			if (_sx < e[i]->getSX() - _cam->getX()) _isEnemyDir = RIGHT;
			// 플레이어가 오른쪽
			if (_sx > e[i]->getSX() - _cam->getX()) _isEnemyDir = LEFT;
		}
		
		// 충돌 처리
		if (getDistance(0, _sy, 0, e[i]->getSY()) <= e[i]->getSize())
		{
			if (IntersectRect(&temp, &PRC, &ERC) && isAtk)// && !_isHit
			{
				switch (atkType)
				{
				case 1: setState(new hit);
					break;
				case 2: setState(new down);
					break;
				default:
					break;
				}
			}
		}
	}	


}


void player::cbState(void* obj)
{
	player* k = (player*)obj;

	image* tempImg = new image;
	tempImg = k->getState()->getPastImage();	// 이전 상태 이미지

	// 이전 상태 이미지가 무엇이냐에 따라서 달라짐 (나중에 enum으로 바꿀 의향 있음)
	if (tempImg == IMAGEMANAGER->findImage("P_IDLE")) k->setState(new idle);
	else if (tempImg == IMAGEMANAGER->findImage("P_WALK")) k->setState(new walk);
	else if (tempImg == IMAGEMANAGER->findImage("P_RUN")) k->setState(new run);
	
	if (tempImg == IMAGEMANAGER->findImage("P_WBATIDLE")) k->setState(new wBatIdle);
	else if (tempImg == IMAGEMANAGER->findImage("P_WBATWALK")) k->setState(new wBatWalk);
	else if (tempImg == IMAGEMANAGER->findImage("P_WBATRUN")) k->setState(new wBatRun);
}

void player::cbIdle(void* obj)
{
	player* k = (player*)obj;
	k->setState(new idle);
}

void player::cbWalk(void* obj)
{
	player* k = (player*)obj;
	k->setState(new walk);
}

void player::cbBatIdle(void* obj)
{
	player* k = (player*)obj;
	k->setState(new wBatIdle);
}

void player::setState(state* state)
{
	// 콜백 때문에 확인용 (이전 상태 이미지)
	state->setPastImage(_state->getImage());

	_state = state; 
	update(); 
	update();
}
