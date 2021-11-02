#pragma once
#include "gameNode.h"

struct MyStruct
{

};

class stageData : public gameNode
{
private:

	POINT genStage1[2];				//스테이지 1 젠 포인트
	POINT genStage2[3];				//스테이지 2 젠 포인트
	POINT genStage3[1];				//스테이지 3 젠 포인트

	void createImage();				//이미지 삽입
	void createGenPoint();			//젠포인트 생성

public:

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	POINT getGen1(int num) { return genStage1[num]; }
	POINT getGen2(int num) { return genStage2[num]; }
	POINT getGen3(int num) { return genStage3[num]; }

};