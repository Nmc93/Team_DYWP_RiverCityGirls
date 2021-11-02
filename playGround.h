#pragma once
#include "gameNode.h"
#include "player.h"
#include "stageManager.h"
#include "itemManager.h"
#include "money.h"
#include "z_order.h"

class playGround : public gameNode
{
private:
	stageManager* _sM;

	//player* _p;

	//camera* _cam;
	
	itemManager* _itemMG;

	z_order* _zO;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

};

