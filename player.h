#pragma once
#include "gameNode.h"
#include "camera.h"
#include "pixelCol.h"

#include <vector>

// 상태
#include "idle.h"
#include "walk.h"
#include "run.h"
#include "atk.h"
#include "jump.h"
#include "sAttack.h"
#include "down.h"
#include "stand.h"
#include "dashAttack.h"
#include "guard.h"
#include "dead.h"
#include "grab.h"
#include "grabFail.h"
#include "pick.h"
#include "hit.h"

// 방망이
#include "wBatIdle.h"
#include "wBatWalk.h"
#include "wBatRun.h"
#include "wBatJump.h"
#include "wBatAttack.h"
#include "wBatThrow.h"

#define GRAVITY 1.0f

enum pAtkType
{
	PNORMALATK = 1,
	PSTRONGATK
};

class player : public gameNode
{
private:

	// 임시로 넣은 오브젝트 움직임
	RECT _orc;
	int _ox, _oy;

	int _timer;

	// 카메라
	camera* _cam;
	pixelCol* _pc;

	// 현 상태
	state* _state;

	// 쉐도우
	image* _shadowImg;
	int _sx, _sy;
	float _speed;			// 좌우 이동 스피드

	// 플레이어
	RECT _shadowRc;			
	bool _isJump;
	float _jumpPower;

	//상태 bool값
	bool _isGrab;
	bool _isGain;		// 득템했어
	
	bool _isAtk;		// 공격맞음?
	int _atkType;
	bool _isHit;		// 맞았음? 그럼 더이상 맞지마셈
	int _isEnemyDir;

	bool _isCameraLock;

	// 뿌릴 애니메이션에 필요한 것들
	float _x, _y;
	RECT _rc;
	RECT _hitBox;
	RECT _atkBox;
	
	
	image* _img;
	int _wDir,_hDir;

	image* _bImg;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();
	void stateRender(animation* motion);
	void move();							// 움직임
	void collision();						// 적 또는 오브젝트와의 충돌

	void playerImage();	// 플레이어 이미지
	void playerAni();	// 플레이어 애니메이션

	void playerHit(player* p, vector<enemy*> e, int distance);	// 적 렉트, 내 렉트, 적 쉐도우와 내 쉐도우의 거리 차
						
	// 콜백 함수들
	static void cbState(void* obj);			// 바로 전 상태로 바꿔주는 콜백함수

	static void cbIdle(void* obj);			// IDLE 상태로 바꿔주는 함수
	static void cbWalk(void* obj);			// IDLE 상태로 바꿔주는 함수
	
	static void cbBatIdle(void* obj);		// BATIDLE 상태로 바꿔주는 함수


	// 뿌릴 애니메이션에 필요한 것들
	float getX() { return _x; }
	void setX(float x) { _x = x; }

	float getY() { return _y; }
	void setY(float y) { _y = y; }

	int getSX() { return _sx; }
	void setSX(float sx) { _sx = sx; }

	int getSY() { return _sy; }
	void setSY(float sy) { _sy = sy; }

	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }

	float getJumpPower() { return _jumpPower; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	RECT getRect() { return _rc; }
	RECT getHitBox() { return _hitBox; }

	void setAtkBox(RECT rc) { _atkBox = rc; };
	RECT getAtkBox() { return _atkBox; }

	int getWDir() { return _wDir; }
	int getHDir() { return _hDir; }

	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }

	image* getImage() { return _img; }

	void setCamera(camera* cam) { _cam = cam; }

	// 바뀐 다음에 바로 렌더를 하니까 이미지가 업뎃 안됐는데(setState된 뒤에 업뎃이 한번더 이루어져야 한다.) 내려와서 되는거다
	void setState(state* state);

	state* getState() { return _state; }

	// getter
	bool getIsCameraLock() { return _isCameraLock; }
	void setIsCameraLock(bool isCameraLock) { _isCameraLock = isCameraLock; }

	//getter
	image* getSImg() { return _shadowImg; }
	RECT getSRc() { return _shadowRc; }
	pixelCol* getPC() { return _pc; }

	//getter
	bool getAtk() { return _isAtk; }
	int getType() { return _atkType; }
	int getEnemyDir() { return _isEnemyDir; }

	// setter
	void setAtk(bool isAtk) { _isAtk = isAtk; }
	void setType(int type) { _atkType = type; }
	void setIsHit(bool isHit) { _isHit = isHit; }
	void setBImg(image* bImg) { _bImg = bImg; }
};

