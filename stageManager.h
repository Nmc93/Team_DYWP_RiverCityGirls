#pragma once
#include "gameNode.h"
#include "enemy.h"
#include <vector>
#include "stageData.h"
#include "player.h"
#include "camera.h"
#include "event.h"
#include <string>

struct tagStage
{
	RECT _rc;				        //배경 렉트
	RECT _rc1, _rc2, _rc3;			    //충돌 렉트
	
	float _x, _y;			        //맵 좌표
	float _a, _s;			        //캐릭터 좌표
	float _d, _f;					//문1 좌표	
	float _d1, _f1;					//문2 좌표				
	image* _stageImg;
};


class stageManager : public gameNode
{
private:

	//스테이지 데이터
	stageData* sData;

	//에너미
	enemy* _em;
	vector<enemy*> _vem;
	vector<enemy*>::iterator _viem;

	//플레이어
	player* _p;
	
	//카메라
	camera* _cam;


	//테스트용
	
	//image* _door; 혹시 몰라서 격리
	
	//이벤트씬
	event* _ev;

	image* _img, * _pixelImg; //배경 이미지 / 픽셀 배경

	int _isCount;  //맵 확인용 카운트
	bool _isCheck; //맵 이동 예외 처리용 bool 값

	bool _isDelete;//스크립트 시작 충돌 렉트 예외처리용 bool 값
	bool _eventBool;	//자물쇠
	int _eventCount;	//이벤트 카운트
	

	tagStage stage;

	vector<tagStage>				_vStage;
	vector<tagStage>::iterator		_viStage;

public:

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	void createEnemy(int stage);			//적 생성
	void deleteEnemy(int num);				//적 제거(0 : 체력적 제거, 1 : 전체 제거)

	vector<enemy*> getEnemyVector() { return _vem; }	//에너미 정보 넘김
	player* getPlayer() { return _p; }					//플레이어 정보 넘김
	event* getEvent() { return _ev; }					//이벤트 정보 넘김
	image* getPixelImage() { return _pixelImg; }		//픽셀 이미지 넘김
	
};

