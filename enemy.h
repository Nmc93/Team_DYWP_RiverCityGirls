#pragma once
#include "gameNode.h"
#include "camera.h"

#define REAACTIONDISTANCE 10	// 목표점 거리
#define WARKSPEED 2				// 이동 속도
#define RANGE 120				// 플레이어와 적의 적정거리

#define ATTRANGE 50				//플레이어와 적의 사거리

#define GRAVITY 0.5f			//중력

//이미지 타입
enum iStateType
{
	SCHOOLGIRL,
	SCHOOLBOY,
	CHEERLEADER,
	BOSS
};

//행동 타입
enum aStateType
{
	EIDLE,
	EWARK,
	ERUN,
	EBLOCK,
	EHIT,
	EDOWN,
	ESTUN1,
	ESTUN2,
	EDIE,
	EJUMP,
	EATT1,
	EATT2,
	EATT3,
	EJATT,
	EDHIT,
	EDATT1,
	EDATT2,
	EMATT,
	ESRUSH,
	ERUSH,
	JATT1,
	JATT2,
	JATT3,
	JATT4
};

//오른쪽 왼짝
enum Lr
{
	ERIGHT,
	ELEFT
};
class enemy : public gameNode
{
private:
	
	camera* _cam;		//카메라

	//패턴 타이머
	int _actTimer;		//패턴 타이머
	int _maxActTimer;	//패턴 실행 시간

	//에너미 타입
	iStateType iType;	// 이미지 타입
	aStateType aType;	// 행동 타입
	Lr lr;				// 좌우

	// 쉐도우
	image* _shadowImg;	// 그림자 이미지
	float _sX, _sY;		// 그림자 중점 좌표
	RECT _shadowRc;		// 그림자 렉트
	float _speed;		// 좌우 이동 스피드

	// 몸통
	image* _img;		//몸통 이미지
	float _bX, _bY;		//몸통 중점좌표
	RECT _bodyRc;		//몸통 렉트
	
	float _rX, _rY;		//실제 좌표
	
	//점프 관련
	bool _isJump;		//점프 bool값
	float _jumpPower;	//점프 파워수치

	//이미지 프레임 관련
	int count[2];		//이미지 프레임 변경 카운트(0 : 카운트 ,1 : 0의 최대치)
	POINT frameNum;		//이미지 프레임 번호

	POINT _playerPosition;	//플레이어 위치 확인용
	float _angle;				//적 이동용 앵글

	//히트박스
	POINT hitBoxWH;		//히트박스 가로 세로크기
	RECT hitBox;		//히트박스 렉트
	bool hit;			//피격 확인
	bool die;			//사망 확인
	//bool hCount;		//연속 피격 방지
	int hitNum;			//피격 종류(0 : 안맞음, 1 : 경직 공격, 2 : 다운 공격)

	//공격 범위
	POINT attBoxWH;		//공격 범위 가로 세로크기
	POINT attBoxXY;		//공격 범위 좌표 보정
	RECT attBox;		//공격 범위 렉트
	int attNum;			//공격 종류(0 : 안맞음, 1 : 경직 공격, 2 : 다운 공격)
	bool attack;		//공격 확인
	int _skillSize;		//y 체크 범위
	int hp;				//체력

	bool _check;		//특수 패턴 확인

	//픽셀충돌
	image* _pixelImage;	//픽셀 이미지

	//테스트
	int testInt;

private: // 함수

	void frameChange();	//프레임 변경
	void imageChange();	//타입에 따른 이미지 변환
	void ai();			// AI 행동 패턴
	void bossAi();		// 보스 AI 행동 패턴
	float enemyJump(float by);	//적 점프(Y축)
	void boxChange();	// 행동에 따른 히트박스 및 공격 범위 변화
	bool pixelColl(int r, int g, int b);	//픽셀 충돌

	void Collision();	//충돌체크

public:

	virtual HRESULT init(iStateType itype, POINT pt); //(에너미 종류,적 스폰 위치)
	virtual void release();
	virtual void update();
	virtual void render();

	//피격 체크(공격 타입,플레이어 렉트 범위, 공격 타입 , y축, y축 검사 범위)
	void setHit(bool att, RECT arc, int type, int sx, int sy, int ysize);

	// 플레이어 위치
	void setSpace(POINT pPosition) { _playerPosition = { pPosition.x,pPosition.y}; }

	image* getSImage() { return _shadowImg; }	// 그림자 이미지
	image* getImage() { return _img; }			// 몸통 이미지

	float getSX() { return _sX; }									//그림자 x중점좌표
	float getSY() { return _sY; }									//그림자 y중점좌표
	float getBX() { return _bX; }									//몸통 x중점좌표
	float getBY() { return _bY; }									//몸통 y중점좌표
	RECT getSRc() { return _shadowRc; }								//그림자 렉트
	RECT getBRc() { return _bodyRc; }								//몸통 렉트
	POINT getFrame() { return frameNum; }							//몸통 y중점좌표
	int getSize() { return _skillSize; }		// y체크 범위

	bool getDie() { if (hp < 0 && _actTimer >= 170) return true; else return false;}	//사망 확인

	void setCam(camera* cam) { _cam = cam; } //카메라 받아오기
	void setPixel(image* pixelimage) { _pixelImage = pixelimage; }	//픽셀 이미지 받아오기
	
    //														
																	
	// 플레이어 실험용으로 만듬 Jo
	int getAttNum() { return attNum; }		//공격 타입
	RECT getAtkBox() { return attBox; }
	bool getAttAck() { return attack; }
	int getAType() { return aType; }

	iStateType getIType() { return iType; }
};