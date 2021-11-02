#include "pch.h"
#include "enemy.h"

HRESULT enemy::init(iStateType itype, POINT pt)
{
	//_cam = new camera;
	//_cam->init();

	//상태 초기화(이미지,행동,좌우)
	iType = itype;
	aType = EIDLE;
	lr = ERIGHT;

	// 그림자 초기화
	_shadowImg = IMAGEMANAGER->findImage("SHADOW");

	_sX = pt.x;
	_sY = pt.y;
	_shadowRc = RectMakeCenter(_sX, _sY, _shadowImg->getWidth(), _shadowImg->getHeight());
	_speed = 0;

	_isJump = false;
	_jumpPower = 0;

	// 몸통 초기화
	if (iType == SCHOOLGIRL)
	{
		_img = IMAGEMANAGER->findImage("SG_IDLE");
		hp = 20;
	}
	else if (iType == SCHOOLBOY)
	{
		_img = IMAGEMANAGER->findImage("SB_IDLE");
		hp = 20;
	}
	else if (iType == BOSS)
	{
		_img = IMAGEMANAGER->findImage("BS_IDLE");
		aType = JATT1;
		hp = 130;
	}

	_bX = _sX;
	_bY = _sY - (_img->getFrameHeight() / 2);
	_bodyRc = RectMakeCenter(_bX, _bY, _img->getFrameWidth(), _img->getFrameHeight());
	
	_rX = _sX;
	_rY = _sY;

	//패턴 타이머 초기화
	_actTimer = 0;
	_maxActTimer = RND->getFromIntTo(50, 200);

	//이미지 프레임 관련 변수 초기화
	count[0] = 0;
	count[1] = 5;

	frameNum.x = frameNum.y = 0;

	//플레이어 위치 초기화
	_playerPosition = { 100,100 };

	//히트박스 초기화
	hitBoxWH = { _img->getFrameWidth(), _img->getFrameHeight()};
	hitBox = RectMakeCenter(_bX, _bY, hitBoxWH.x, hitBoxWH.y);

	//피격 및 공격 종류 초기화
	hitNum = 0;
	attNum = 0;
	_skillSize = 0;

	//공격 박스 크기 초기화(타입별 크기 조정)
	if (iType == SCHOOLGIRL) attBoxWH = {120,50};
	else if (iType == SCHOOLBOY) attBoxWH = { 120,50};

	//공격 범위 중점 조절
	attBoxXY = {30,30};

	//공격 박스 렉트 초기화(좌우에 따른 공격범위 위치 보정)
	if (lr == ERIGHT) attBox = RectMakeCenter(_bX + attBoxXY.x, _bY, attBoxWH.x, attBoxWH.y);
	else if (lr == ELEFT) attBox = RectMakeCenter(_bX - attBoxXY.x, _bY, attBoxWH.x, attBoxWH.y);

	//공격,특수패턴,연속피격 방지
	attack = false;
	_check = false;
	die = false;
	//hCount = false;

    return S_OK;
}

void enemy::release()
{
}

//업데이트
void enemy::update()
{
	
	//에너미 AI
	Collision();
	//if (KEYMANAGER->isToggleKey(VK_NUMPAD5))
	//{
	if (iType == BOSS) bossAi();
	else ai();
	//}
	//이미지의 프레임 돌리는 함수
	frameChange();

	//공격 범위 변경
	boxChange();

	//그림자 & 몸통 업데이트
	_shadowRc = RectMakeCenter(_sX - _cam->getX(), _sY - _cam->getY(), _shadowImg->getWidth(), _shadowImg->getHeight());
	_bX = _sX;
	_bY = enemyJump(_bY);
	_bodyRc = RectMakeCenter(_bX - _cam->getX(), _bY - _cam->getY(), _img->getFrameWidth(), _img->getFrameHeight());

	//히트박스
	hitBox = RectMakeCenter(_bX - _cam->getX(), _bY - _cam->getY(), hitBoxWH.x, hitBoxWH.y);

	//공격 박스 렉트 초기화(좌우에 따른 공격 범위 위치 보정)
	if (lr == ERIGHT) attBox = RectMakeCenter((_bX - _cam->getX()) + attBoxXY.x, _bY - _cam->getY() - attBoxXY.y, attBoxWH.x, attBoxWH.y);
	else if (lr == ELEFT) attBox = RectMakeCenter((_bX - _cam->getX()) - attBoxXY.x, _bY - _cam->getY() - attBoxXY.y, attBoxWH.x, attBoxWH.y);

}

//랜더
void enemy::render()
{
	//_shadowImg->render(getMemDC(),_shadowRc.left, _shadowRc.top);
	//_img->frameRender(getMemDC(), _bodyRc.left, _bodyRc.top, frameNum.x, frameNum.y);

	//캐릭터 렉트 출력
	if (KEYMANAGER->isToggleKey(VK_F11))
	{
		Rectangle(getMemDC(), _shadowRc);	//그림자 렉트
		//Rectangle(getMemDC(), _bodyRc);	//몸통 렉트
		Rectangle(getMemDC(), hitBox);		//히트박스 렉트
		Rectangle(getMemDC(), attBox);		//공격범위 렉트
	}
	//좌표 및 정보 출력
	if (KEYMANAGER->isToggleKey(VK_F9))
	{
		char testTest[128];
		sprintf_s(testTest, "X:%.f Y:%.f", _rX, _rY);
		TextOut(getMemDC(), _bodyRc.right, _bodyRc.top, testTest, strlen(testTest));
		char testTest1[128];
		sprintf_s(testTest1, "jp :%d , AS : %d", _isJump, aType);
		TextOut(getMemDC(), _bodyRc.right, _bodyRc.top + 15, testTest1, strlen(testTest1));
		char testTest2[128];
		sprintf_s(testTest2, "tm :%d , xtm : %d", _actTimer, _maxActTimer);
		TextOut(getMemDC(), _bodyRc.right, _bodyRc.top + 30, testTest2, strlen(testTest2));
		char testTest3[128];
		sprintf_s(testTest3, "HP : %d ", hp);
		TextOut(getMemDC(), _bodyRc.right, _bodyRc.top + 45, testTest3, strlen(testTest3));
	}
}

//피격 체크(공격여부,공격범위,공격타입,y축,검색범위)
void enemy::setHit(bool att,RECT arc, int type, int sx, int sy, int ysize)
{
	if (aType != EDOWN && aType != JATT1 && aType != EDATT1 && aType != EDATT2 && aType != EDIE)
	{
		//플레이어가 sY의 일정범위 내이고 att(공격 여부) 가 참일때
		if (sy < _sY + ysize && sy > _sY - ysize && att)
		{
			RECT tRc;
			//적 공격 범위가 히트박스가 겹쳤을 때
			if (IntersectRect(&tRc, &arc, &hitBox))
			{
				if (aType != ESTUN1 && aType != EDHIT && sx >= _sX - _cam->getX()) lr = ERIGHT;
				else if(aType != ESTUN1 && aType != EDHIT && sx < _sX - _cam->getX()) lr = ELEFT;
				//공격 당했고 무엇에 공격을 당했는지 지정
				hit = att;
				hitNum = type;
			}
		}
	}
}

//이미지 프레임 변경
void enemy::frameChange()
{
	count[0]++;

	//lr에 따른 이미지프레임y 변경
	if (lr == ERIGHT && aType != ERUSH) frameNum.y = 0;
	else if(lr == ELEFT && aType != ERUSH) frameNum.y = 1;

	//0의 값이 1의 값을 넘거나 같다진다면 이미지 프레임 재생
	if (count[0] >= count[1])
	{
		//방향이 RIGHT일때
		if (lr == ERIGHT)
		{
			frameNum.x++;
			if (iType != BOSS && aType == EDIE && frameNum.x >= 17) frameNum.x = 17;
			if (iType == BOSS && aType == EDIE && frameNum.x >= _img->getMaxFrameX())
			{
				frameNum.x = 9;
			}
			else if (frameNum.x > _img->getMaxFrameX())
			{
				if (aType != EHIT && aType != EDOWN) frameNum.x = 0;
				else frameNum.x = _img->getMaxFrameX();
			}
		}
		//방향이 LEFT일때
		else if (lr == ELEFT)
		{
			frameNum.x--;
			if (iType != BOSS && aType == EDIE && frameNum.x <= 9) frameNum.x = 9;
			if (iType == BOSS && aType == EDIE && frameNum.x <= 0)
			{
				frameNum.x = 3;
			}
			else if (frameNum.x < 0)
			{
				if (aType != EHIT && aType != EDOWN && aType != EDIE) frameNum.x = _img->getMaxFrameX();
				else frameNum.x = 0;
			}
		}
		count[0] = 0;
	}
}

//보스의 행동 패턴
void enemy::bossAi()
{
	//패턴 타이머
	_actTimer++;
	
	//플레이어와 에너미의 거리
	int Distance = 0;
	//플레이어와 에너미의 앵글값
	int angle = 0;
	//행동 랜덤 체크
	int active = 0;
	
	//==============================================================================
	//=============== lr에 따른 Distance,angle 계산 =================================
	//==============================================================================
	
	//좌우에 따른 거리와 앵글값 계산
	if (lr == ELEFT)
	{
		Distance = sqrtf(powf(((_sX - _cam->getX()) - RANGE) - _playerPosition.x, 2) + powf((_sY - _cam->getY()) - _playerPosition.y, 2));
		angle = -atan2f((_playerPosition.y - (_sY - _cam->getY())), (_playerPosition.x - ((_sX - _cam->getX()) - RANGE)));
	}
	else if (lr == ERIGHT)
	{
		Distance = sqrtf(powf(((_sX - _cam->getX()) + RANGE) - _playerPosition.x, 2) + powf((_sY - _cam->getY()) - _playerPosition.y, 2));
		angle = -atan2f((_playerPosition.y - (_sY - _cam->getY())), (_playerPosition.x - ((_sX - _cam->getX()) + RANGE)));
	}
	
	//사망
	if (hp < 0 && die == false)
	{
		die = true;
		aType = EDIE;
		imageChange();
	}
	//=============================== EIDLE ==============================
	if (aType == EIDLE)
	{
		//행동 타이머가 돌았다면
		if (_actTimer >= _maxActTimer)
		{
			//타이머 초기화
			_actTimer = 0;
	
			//랜덤 패턴 초기화
			active = RND->getFromIntTo(0, 6);
	
			//거리가 목표거리보다 멀거나 같다면
			if (Distance >= REAACTIONDISTANCE)
			{
				//행동 타입 변경(거리에 따른 변경) 범위내 공격 예정
				if (Distance <= 200)
				{
					//움직이거나 대하거나
					if (active != 2) aType = EWARK;
					else if (active == 2)
					{
						aType = EMATT;
						//앵글 재조정
						_angle = -atan2f(_playerPosition.y - (_sY - _cam->getY()), _playerPosition.x - ((_sX - _cam->getX())));
					}
				}
				else if (Distance > 200)
				{
					if (active == 2) aType = JATT1;
					else if (active != 2) aType = EWARK;
				}
				//행동 타입에 따른 이미지 변경EMATT
				imageChange();
				//패턴타이머 초기화
				_maxActTimer = RND->getFromIntTo(50, 200);
			}
			//거리가 목표거리 내라면
			else if (Distance < REAACTIONDISTANCE)
			{
				//멍때리거나 때리거나
				if (active != 0)
				{
					if(active == 1 || active == 5) aType = EATT1;
					else if (active == 2 || active == 3) aType = EATT2;
					else if (active == 4) aType = EATT3;
					
					imageChange();
					//_maxActTimer = RND->getFromIntTo(50, 200);
				}
			}
		}
		//좌우에 따른 상태 변화
		if (_sX - _cam->getX() <= _playerPosition.x) lr = ERIGHT;
		else if (_sX - _cam->getX() > _playerPosition.x) lr = ELEFT;
	}
	//=============================== EWARK ==============================
	else if (aType == EWARK)
	{
		//행동 타이머가 돌거나 플레이어 주변에 
		if (_actTimer >= _maxActTimer || Distance < REAACTIONDISTANCE)
		{
			//타이머 초기화
			_actTimer = 0;
			//대기 상태로 변환
			aType = EIDLE;
			//상태에 따른 이미지 변환
			imageChange();
	
			//종료 이유에 따른 패턴타이머 초기화
			if (_actTimer >= _maxActTimer) _maxActTimer = RND->getFromIntTo(50, 200);
			else if (Distance < REAACTIONDISTANCE) _maxActTimer = 2;
		}
		//행동 타이머가 다 돌지 않았다면
		else
		{
			//타입에 따른 속도 변화
			_speed = WARKSPEED * 2;
	
			_sX += cosf(angle) * _speed;
			_sY += -sinf(angle) * _speed;
			_rX += cosf(angle) * _speed;
			_rY += -sinf(angle) * _speed;
		}
		//좌우에 따른 상태 변화
		if (_sX - _cam->getX() <= _playerPosition.x) lr = ERIGHT;
		else if (_sX - _cam->getX() > _playerPosition.x) lr = ELEFT;
	}

	//=============================== EATT1 ==============================
	else if (aType == EATT1 || aType == EATT2 || aType == EATT3)//(엘보,슬랩)
	{
		//오른쪽 왼쪽
		if (lr == ERIGHT)
		{

			//프레임의 끝에 도달했을 때
			if (frameNum.x >= _img->getMaxFrameX())
			{
				aType = EIDLE;
				imageChange();
				_maxActTimer = RND->getFromIntTo(50, 200);
			}
		}
		else if (lr == ELEFT)
		{
			//프레임의 끝에 도달했을 때
			if (frameNum.x <= 0)
			{
				aType = EIDLE;
				imageChange();
				_maxActTimer = RND->getFromIntTo(50, 200);
			}
		}
	}
	//=============== 경직 및 다운 ============================
	else if (aType == EHIT)
	{
		if (_actTimer >= 40)
		{
			aType = EIDLE;
			imageChange();
			_actTimer = 0;
		}
	}
	else if (aType == EDOWN)
	{
		//민트 색 체크
		if (pixelColl(0, 255, 255))
		{
			if (lr == ERIGHT)
			{
				lr = ELEFT;
				frameNum.x = _img->getMaxFrameX();
			}
			else if (lr == ELEFT)
			{
				lr = ERIGHT;
				frameNum.x = 0;
			}
		}
		//RIGHT일때 패턴
		if (lr == ERIGHT)
		{
			if (frameNum.x == 0)
			{
				_isJump = true;
				_jumpPower = 6;
			}
			else if (frameNum.x == 9)
			{
				_isJump = true;
				_jumpPower = 4;
			}
			if (frameNum.x < 13)
			{
				_sX -= 3;
				_rX -= 3;
			}
		}
		//LEFT일때 패턴
		if (lr == ELEFT)
		{
			if (frameNum.x == _img->getMaxFrameX())
			{
				_isJump = true;
				_jumpPower = 6;
			}
			else if (frameNum.x == 13)
			{
				_isJump = true;
				_jumpPower = 4;
			}
			if (frameNum.x > 7)
			{
				_sX += 3;
				_rX += 3;
			}
		}
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
			lr == ELEFT && frameNum.x <= 0)
		{
			aType = ESTUN1;
			imageChange();
			_actTimer = 0;
		}
	}
	//=============================== ESTUN ==============================
	else if (aType == ESTUN1)
	{
		if (_actTimer >= 100)
		{
			//스턴 상태일때 공격당했다면
			if (_check)
			{
				aType = EDATT1;
				imageChange();
				_check = false;
				_actTimer = 0;
			}
			else
			{
				aType = ESTUN2;
				imageChange();
				_actTimer = 0;
			}
		}
	}
	//========================== EDATT1,2 ESTUN2 ============================
	else if (aType == EDATT1 || aType == EDATT2 || aType == ESTUN2)
	{
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
			lr == ELEFT && frameNum.x <= 0)
		{
			if (aType == EDATT1)
			{
				aType = EDATT2;
				imageChange();
				_actTimer = 0;
			}
			else if (aType == EDATT2 || aType == ESTUN2)
			{
				aType = EIDLE;
				imageChange();
				_actTimer = 0;
			}
		}
	}
	//=============================== EDHIT ==============================
	else if (aType == EDHIT)
	{
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
			lr == ELEFT && frameNum.x <= 0)
		{
			aType = ESTUN1;
			imageChange();
		}
	}
	//=============================== EMATT ==============================
	else if (aType == EMATT)
	{
	
		if (lr == ERIGHT && frameNum.x >= 14 && frameNum.x <= 18 ||
			lr == ELEFT && frameNum.x >= 10 && frameNum.x <= 14)
		{
			//타입에 따른 속도 변화
			_speed = WARKSPEED * 4;
	
			_sX += cosf(_angle) * _speed;
			_sY += -sinf(_angle) * _speed;
			_rX += cosf(_angle) * _speed;
			_rY += -sinf(_angle) * _speed;
		}
		if (lr == ERIGHT && Distance < 10) frameNum.x = 17;
		else if(lr == ELEFT && Distance < 10) frameNum.x = 9;
		
		//나온 값으로 바로 보정
		_shadowRc = RectMakeCenter(_sX - _cam->getX(), _sY - _cam->getY(), _shadowImg->getWidth(), _shadowImg->getHeight());
	
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
			lr == ELEFT && frameNum.x <= 0)
		{
			aType = EIDLE;
			imageChange();
			_actTimer = 0;
		}
	}
	//=============================== EJATT ==============================
	else if (aType == JATT1 || aType == JATT2 || aType == JATT3 || aType == JATT4)
	{
		if (aType == JATT1)
		{
			if (lr == ERIGHT && frameNum.x >= 7 ||
				lr == ELEFT && frameNum.x <= 2)
			{
				aType = JATT2;
				imageChange();
				_jumpPower = 30;
				_isJump = true;
				_actTimer = 0;
			}
		}
		else if (aType == JATT2)
		{
			//추적
			_angle = -atan2f(_playerPosition.y - (_sY - _cam->getY()), _playerPosition.x - ((_sX - _cam->getX())));
			_speed = WARKSPEED * 4;
			_sX += cosf(_angle) * _speed;
			_sY += -sinf(_angle) * _speed;
			_rX += cosf(_angle) * _speed;
			_rY += -sinf(_angle) * _speed;
			_shadowRc = RectMakeCenter(_sX - _cam->getX(), _sY - _cam->getY(), _shadowImg->getWidth(), _shadowImg->getHeight());
			
			if (_actTimer > 100)
			{
				aType = JATT3;
				imageChange();
				_actTimer = 0;
			}
		}
		else if(aType == JATT3)
		{
			if (!_isJump)
			{
				aType = JATT4;
				imageChange();
				_actTimer = 0;
			}
		}
		else if (aType == JATT4)
		{
			if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
				lr == ELEFT && frameNum.x <= 0)
			{
				aType = EIDLE;
				imageChange();
				_actTimer = 0;
			}
		}
	}
}

//행동 패턴
void enemy::ai()
{
	//패턴 타이머
	_actTimer++;

	//플레이어와 에너미의 거리
	int Distance = 0;
	//플레이어와 에너미의 앵글값
	int angle = 0;
	//행동 랜덤 체크
	int active = 0;

	//==============================================================================
	//=============== lr에 따른 Distance,angle 계산 =================================
	//==============================================================================

	//좌우에 따른 거리와 앵글값 계산
	if (lr == ELEFT)
	{
		Distance = sqrtf(powf(((_sX - _cam->getX()) - RANGE) - _playerPosition.x, 2) + powf((_sY - _cam->getY()) - _playerPosition.y, 2));
		angle = -atan2f((_playerPosition.y - (_sY - _cam->getY())), (_playerPosition.x - ((_sX - _cam->getX()) - RANGE)));
	}
	else if (lr == ERIGHT)
	{
		Distance = sqrtf(powf(((_sX - _cam->getX()) + RANGE) - _playerPosition.x, 2) + powf((_sY - _cam->getY()) - _playerPosition.y, 2));
		angle = -atan2f((_playerPosition.y - (_sY - _cam->getY())), (_playerPosition.x - ((_sX - _cam->getX()) + RANGE)));
	}

	testInt = Distance;

	//==============================================================================
	//=============== aType에 따른 움직임 및 aType 변경==============================
	//==============================================================================
	//사망
	if (hp < 0 && die == false)
	{
		die = true;
		aType = EDIE;
		imageChange();
	}
	//=============== 대기중 ==============================
	if (aType == EIDLE)
	{
		//행동 타이머가 돌았다면
		if (_actTimer >= _maxActTimer)
		{
			//타이머 초기화
			_actTimer = 0;

			//랜덤 패턴 초기화
			active = RND->getFromIntTo(0, 4);

			//거리가 목표거리보다 멀거나 같다면
			if (Distance >= REAACTIONDISTANCE)
			{
				//움직이거나 대기하거나
				if (active != 2)
				{
					//행동 타입 변경(거리에 따른 변경)
					if (Distance <= 350) aType = EWARK;
					else if (Distance > 350) aType = ERUN;
					//행동 타입에 따른 이미지 변경
					imageChange();
				}
				//패턴타이머 초기화
				_maxActTimer = RND->getFromIntTo(50, 200);
			}
			//거리가 목표거리 내라면
			else if (Distance < REAACTIONDISTANCE)
			{	
				//멍때리거나 때리거나
				if (active != 2)
				{
					aType = EATT1;
					imageChange();
					//_maxActTimer = RND->getFromIntTo(50, 200);
				}
			}
		}
		//좌우에 따른 상태 변화
		if (_sX - _cam->getX() <= _playerPosition.x) lr = ERIGHT;
		else if (_sX - _cam->getX() > _playerPosition.x) lr = ELEFT;
	}
	//=============== 걷기 & 뛰기 ==============================
	else if (aType == EWARK || aType == ERUN)
	{
		//행동 타이머가 돌거나 플레이어 주변에 
		if (_actTimer >= _maxActTimer || Distance < REAACTIONDISTANCE)
		{
			//타이머 초기화
			_actTimer = 0;
			//대기 상태로 변환ds
			aType = EIDLE;
			//상태에 따른 이미지 변환
			imageChange();

			//종료 이유에 따른 패턴타이머 초기화
			if (_actTimer >= _maxActTimer) _maxActTimer = RND->getFromIntTo(50, 200);
			else if (Distance < REAACTIONDISTANCE) _maxActTimer = 2;
		}
		//행동 타이머가 다 돌지 않았다면
		else
		{
			//타입에 따른 속도 변화
			if (aType == EWARK) _speed = WARKSPEED;
			else if (aType == ERUN) _speed = WARKSPEED * 2;

			_sX += cosf(angle) * _speed;
			_sY += -sinf(angle) * _speed;
			_rX += cosf(angle) * _speed;
			_rY += -sinf(angle) * _speed;
		}
		//좌우에 따른 상태 변화
		if (_sX - _cam->getX() <= _playerPosition.x) lr = ERIGHT;
		else if (_sX - _cam->getX() > _playerPosition.x) lr = ELEFT;
	}
	//=============== 연속 공격 ==============================
	else if (aType == EATT1 || aType == EATT2 || aType == EATT3)
	{
		//타이머 초기화
		_actTimer = 0;
		
		//콤보 공격
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX()||
			lr == ELEFT && frameNum.x <= 0)
		{
			if (aType == EATT1)
			{
				aType = EATT2;
				//상태에 따른 이미지 변환
				imageChange();
			}
			else if (aType == EATT2)
			{
				aType = EATT3;
				//상태에 따른 이미지 변환
				imageChange();
			}
			else if (aType == EATT3)
			{
				aType = EIDLE;
				//상태에 따른 이미지 변환
				imageChange();
				//패턴타이머 초기화
				_maxActTimer = RND->getFromIntTo(50, 200);
			}
		}
	}
	//=============== 경직 및 다운 ============================
	else if (aType == EHIT)
	{
		if (_actTimer >= 40)
		{
			aType = EIDLE;
			imageChange();
			_actTimer = 0;
		}
	}
	else if (aType == EDOWN)
	{
		//민트 색 체크
		if (pixelColl(0, 255, 255))
		{
			if (lr == ERIGHT)
			{
				lr = ELEFT;
				frameNum.x = _img->getMaxFrameX();
			}
			else if (lr == ELEFT)
			{
				lr = ERIGHT;
				frameNum.x = 0;
			}
		}

		//RIGHT일때 16프레임 
		if (lr == ERIGHT)
		{
			if (frameNum.x == 0)
			{
				_isJump = true;
				_jumpPower = 6;
			}
			if (frameNum.x < 15)
			{
				_sX -= 3;
				_rX -= 3;
			}
		}
		//LEFT일때
		if (lr == ELEFT)
		{
			if (frameNum.x == _img->getMaxFrameX())
			{
				_isJump = true;
				_jumpPower = 6;
			}
			if (frameNum.x > 11)
			{
				_sX += 3;
				_rX += 3;
			}
		}
		if (lr == ERIGHT && frameNum.x >= _img->getMaxFrameX() ||
			lr == ELEFT && frameNum.x <= 0)
		{
			aType = EIDLE;
			imageChange();
			_actTimer = 0;
		}
	}
}

//점프
float enemy::enemyJump(float by)
{
	//_bY계산
	if (_isJump)
	{
		by -= _jumpPower;
		_jumpPower -= GRAVITY;
		//점프 끝내기
		if (by >= _sY - (_img->getFrameHeight() / 2)) _isJump = false;
	}
	else if (!_isJump)
	{
		by = _sY - (_img->getFrameHeight() / 2);
		_jumpPower = 0;
	}
	return by;
}

//이미지 변경
void enemy::imageChange()
{
	//행동에 따른 분류
	if (aType == EIDLE)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_IDLE");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_IDLE");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_IDLE");
	}
	else if (aType == EWARK)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_WARK");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_WARK");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_WARK");
	}
	else if (aType == ERUN)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_RUN");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_RUN");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_WARK");
	}
	else if (aType == EBLOCK)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_BLOCK");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_BLOCK");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img;
	}
	else if (aType == EHIT)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_HIT");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_HIT");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_HIT3");
	}
	else if (aType == EDOWN)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_DOWN");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_DOWN");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_DOWN");
	}
	else if (aType == EDHIT)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_DOWN");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_DOWN");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_DHIT");
	}
	else if (aType == ESTUN1)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_STUN");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_STUN");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_STUN1");
	}
	else if (aType == ESTUN2)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_STUN2");
	}
	else if (aType == EDIE)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_DOWN");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_DOWN");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_DIE");
	}
	else if (aType == EJUMP)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_JUMP");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_JUMP");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img;
	}
	else if (aType == EATT1)
		{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_ATT1");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_ATT1");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_ATT1");
	}
	else if (aType == EATT2)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_ATT2");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_ATT2");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_SLAP");
	}
	else if (aType == EATT3)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_ATT3");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_ATT3");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_ROAR");
	}
	else if (aType == EJATT)
	{
		if (iType == SCHOOLGIRL) _img = IMAGEMANAGER->findImage("SG_JATT");
		else if (iType == SCHOOLBOY) _img = IMAGEMANAGER->findImage("SB_JATT");
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img;
	}
	else if (aType == EDATT1)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_DATT1");
	}
	else if (aType == EDATT2)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_DATT2");
	}
	else if (aType == EMATT)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_MATT");
	}
	else if (aType == ESRUSH)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_RUN");
	}
	else if (aType == ERUSH)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_RUSH");
	}
	else if (aType == JATT1)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_JATT1");
	}
	else if (aType == JATT2)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_JATT2");
	}
	else if (aType == JATT3)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_JATT3");
	}
	else if (aType == JATT4)
	{
		if (iType == SCHOOLGIRL) _img;
		else if (iType == SCHOOLBOY) _img;
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img = IMAGEMANAGER->findImage("BS_JATT4");
	}

	//종료하면서 프레임x 를 초기화
	if(lr == ERIGHT) frameNum.x = 0;
	else if(lr == ELEFT) frameNum.x = _img->getMaxFrameX();
}

//히트박스 & 공격범위 변경
void enemy::boxChange()
{
	//행동에 따른 분류
	//{ attBoxWH = { 가로,세로 }; attBoxXY = { x,y }; }
	if (aType == EIDLE || aType == EWARK || aType == ERUN || aType == EBLOCK || aType == EHIT || aType == EDOWN || aType == ESTUN1 || aType == EDIE || aType == EJUMP)
	{
		if (iType == SCHOOLGIRL) { attBoxWH = { 0,0 }; attBoxXY = { 0,0 }; }
		else if (iType == SCHOOLBOY) { attBoxWH = { 0,0 }; attBoxXY = { 0,0 }; }
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) { attBoxWH = { 0,0 }; attBoxXY = { 0,0 }; };

		attack = false;
	}
	else if (aType == EATT1)
	{
		if (iType == SCHOOLGIRL)
		{ 
			if (lr == ERIGHT && aType == EATT1 && frameNum.x == 2) attack = true;
			else if (lr == ERIGHT && aType == EATT1 && frameNum.x == 3)attack = false;
			if (lr == ELEFT && aType == EATT1 && frameNum.x == 4) attack = true;
			else if (lr == ELEFT && aType == EATT1 && frameNum.x == 3)attack = false;
			
			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 120,50 }; attBoxXY = { 30,40 };
		}
		else if (iType == SCHOOLBOY)
		{ 
			if (lr == ERIGHT && aType == EATT1 && frameNum.x == 2) attack = true;
			else if (lr == ERIGHT && aType == EATT1 && frameNum.x == 3)attack = false;
			if (lr == ELEFT && aType == EATT1 && frameNum.x == 4) attack = true;
			else if (lr == ELEFT && aType == EATT1 && frameNum.x == 3)attack = false;
			
			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 170,50 }; attBoxXY = { 80,40 }; 
		}
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS)
		{
			if (lr == ERIGHT && aType == EATT1 && frameNum.x == 5) attack = true;
			else if (lr == ERIGHT && aType == EATT1 && frameNum.x == 6)attack = false;
			if (lr == ELEFT && aType == EATT1 && frameNum.x == 5) attack = true;
			else if (lr == ELEFT && aType == EATT1 && frameNum.x == 4)attack = false;
			
			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 120,180 }; attBoxXY = { 80,30 };
		}
		//attack = true;
	}
	else if (aType == EATT2)
	{
		if (iType == SCHOOLGIRL) 
		{ 
			if (lr == ERIGHT && aType == EATT2 && frameNum.x == 2) attack = true;
			else if (lr == ERIGHT && aType == EATT2 && frameNum.x == 3)attack = false;
			if (lr == ELEFT && aType == EATT2 && frameNum.x == 5) attack = true;
			else if (lr == ELEFT && aType == EATT2 && frameNum.x == 4)attack = false;

			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 150,70 }; attBoxXY = { 60,50 }; 
		}
		else if (iType == SCHOOLBOY)
		{ 
			if (lr == ERIGHT && aType == EATT2 && frameNum.x == 2) attack = true;
			else if (lr == ERIGHT && aType == EATT2 && frameNum.x == 3)attack = false;
			if (lr == ELEFT && aType == EATT2 && frameNum.x == 4) attack = true;
			else if (lr == ELEFT && aType == EATT2 && frameNum.x == 3)attack = false;

			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 150,70 }; attBoxXY = { 60,50 }; 
		}
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS)
		{ 
			if (lr == ERIGHT && aType == EATT2 && frameNum.x == 8) attack = true;
			else if (lr == ERIGHT && aType == EATT2 && frameNum.x == 9)attack = false;
			if (lr == ELEFT && aType == EATT2 && frameNum.x == 5) attack = true;
			else if (lr == ELEFT && aType == EATT2 && frameNum.x == 4)attack = false;
			
			_skillSize = 40;
			attNum = 1;
			attBoxWH = { 310,140 }; attBoxXY = { 30,50 }; 
		}
		//attack = true;
	}
	else if (aType == EATT3)
	{
		if (iType == SCHOOLGIRL) 
		{ 
			if (lr == ERIGHT && aType == EATT3 && frameNum.x == 6) attack = true;
			else if (lr == ERIGHT && aType == EATT3 && frameNum.x == 7)attack = false;
			if (lr == ELEFT && aType == EATT3 && frameNum.x == 5) attack = true;
			else if (lr == ELEFT && aType == EATT3 && frameNum.x == 4)attack = false;

			_skillSize = 40;
			attNum = 2;
			attBoxWH = { 135,60 }; attBoxXY = { 45,30 }; 
		}
		else if (iType == SCHOOLBOY)
		{ 
			if (lr == ERIGHT && aType == EATT3 && frameNum.x == 3) attack = true;
			else if (lr == ERIGHT && aType == EATT3 && frameNum.x == 4)attack = false;
			if (lr == ELEFT && aType == EATT3 && frameNum.x == 5) attack = true;
			else if (lr == ELEFT && aType == EATT3 && frameNum.x == 4)attack = false;

			_skillSize = 40;
			attNum = 2;
			attBoxWH = { 135,220 }; attBoxXY = { 45,40 }; 
		}
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) 
		{ 
			if (lr == ERIGHT && aType == EATT3 && frameNum.x == 5) attack = true;
			else if (lr == ERIGHT && aType == EATT3 && frameNum.x == 11)attack = false;
			if (lr == ELEFT && aType == EATT3 && frameNum.x == 6) attack = true;
			else if (lr == ELEFT && aType == EATT3 && frameNum.x == 0)attack = false;
			
			_skillSize = 60;
			attNum = 2;
			attBoxWH = { 280,250 }; attBoxXY = { 0,0 }; 
		}
	}
	else if (aType == EJATT)
	{
		if (iType == SCHOOLGIRL) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == SCHOOLBOY) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) _img;

		attack = true;
	}
	else if (aType == EMATT)
	{
		if (iType == SCHOOLGIRL) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == SCHOOLBOY) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) 
		{
			if (lr == ERIGHT && aType == EMATT && frameNum.x == 17) attack = true;
			else if (lr == ERIGHT && aType == EMATT && frameNum.x == 18)attack = false;
			if (lr == ELEFT && aType == EMATT && frameNum.x == 9) attack = true;
			else if (lr == ELEFT && aType == EMATT && frameNum.x == 8)attack = false;

			_skillSize = 40;
			attNum = 2;
			attBoxWH = { 275,190 }; attBoxXY = { 90,0 }; 
		}
	}
	else if (aType == EDATT1)
	{
		if (iType == SCHOOLGIRL) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == SCHOOLBOY) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) 
		{
			if (lr == ERIGHT && aType == EDATT1 && frameNum.x == 8) attack = true;
			else if (lr == ERIGHT && aType == EDATT1 && frameNum.x == 9)attack = false;
			if (lr == ELEFT && aType == EDATT1 && frameNum.x == 1) attack = true;
			else if (lr == ELEFT && aType == EDATT1 && frameNum.x == 0)attack = false;
			
			_skillSize = 60;
			attNum = 2;
			attBoxWH = { 275,190 }; attBoxXY = { 0,0 }; 
		}
	}
	else if (aType == JATT4)
	{
		if (iType == SCHOOLGIRL) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == SCHOOLBOY) { attBoxWH = { 120,50 }; attBoxXY = { 30,30 }; }
		else if (iType == CHEERLEADER) _img;
		else if (iType == BOSS) 
		{ 
			if (lr == ERIGHT && aType == JATT4 && frameNum.x == 3) attack = true;
			else if (lr == ERIGHT && aType == JATT4 && frameNum.x == 4)attack = false;
			if (lr == ELEFT && aType == JATT4 && frameNum.x == 15) attack = true;
			else if (lr == ELEFT && aType == JATT4 && frameNum.x == 14)attack = false;

			_skillSize = 100;
			attNum = 2;
			attBoxWH = { 500,250 }; attBoxXY = { 0,-100 }; 
		}
	}
}

//픽셀충돌
bool enemy::pixelColl(int r, int g, int b)
{
	//================= LEFT, Y
	COLORREF color = GetPixel(_pixelImage->getMemDC(), _rX - _shadowImg->getWidth() / 2, _rY);

	int ir = GetRValue(color);
	int ig = GetGValue(color);
	int ib = GetBValue(color);

	if ((ir == r && ig == g && ib == b)) return true;
	
	//================= RIGHT, Y
	color = GetPixel(_pixelImage->getMemDC(), _rX + _shadowImg->getWidth() / 2, _rY);

	ir = GetRValue(color);
	ig = GetGValue(color);
	ib = GetBValue(color);

	if ((ir == r && ig == g && ib == b)) return true;

	//================= X, TOP
	color = GetPixel(_pixelImage->getMemDC(), _rX, _rY - _shadowImg ->getHeight() / 2);

	ir = GetRValue(color);
	ig = GetGValue(color);
	ib = GetBValue(color);

	if ((ir == r && ig == g && ib == b)) return true;

	//================= X, BOTTOM
	color = GetPixel(_pixelImage->getMemDC(), _rX, _rY + _shadowImg->getHeight() / 2);

	ir = GetRValue(color);
	ig = GetGValue(color);
	ib = GetBValue(color);

	if ((ir == r && ig == g && ib == b)) return true;
	
	//================= END
	return false;
}

//충돌체크
void enemy::Collision()
{
	if (iType == BOSS)
	{
		//피격을 당했고 종류가 확실할 때
		if (hit && hitNum != 0)
		{
			//종류가 경직일 경우
			if (hitNum == 1)
			{
				if (aType != ESTUN1 && aType != EDHIT)
				{
					aType = EHIT;
					imageChange();
				}
				else if (aType == ESTUN1)
				{
					_check = true;
					aType = EDHIT;
					imageChange();
				}
				hp -= 1;
			}
			//종류가 다운일 경우
			else if (hitNum == 2)
			{
				if (aType != ESTUN1 && aType != EDHIT)
				{
					aType = EDOWN;
					imageChange();
				}
				else if (aType == ESTUN1)
				{
					_check = true;
					aType = EDHIT;
					imageChange();
				}
				hp -= 3;
			}
		}
	}
	else
	{
		//=============== 피격 ==============================
		//피격을 당했고 종류가 확실할 때
		if (hit && hitNum != 0)
		{
			//종류가 경직일 경우
			if (hitNum == 1)
			{
				aType = EHIT;
				imageChange();
				hp -= 1;
			}
			//종류가 다운일 경우
			else if (hitNum == 2)
			{
				aType = EDOWN;
				imageChange();
				hp -= 3;
			}
			//타이머 초기화
			_actTimer = 0;
		}
	}
	// 피격 초기화
	hit = false;
	hitNum = 0;
}
