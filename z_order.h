#pragma once
#include"gameNode.h"
#include"stageManager.h"
#include"player.h"
#include"itemManager.h"
#include <vector>

enum kind	//오브젝트 키값
{
	PL,	//플레이어
	EM,	//적
	IT	//아이템
};

struct object
{
	kind key;		//종류
	image* img;		//이미지
	image* sImg;	//그림자 이미지
	float bX, bY;	//몸통 중점 좌표
	RECT bRc;		//몸통 렉트
	float sX, sY;	//그림자 중점 좌표
	RECT sRc;		//그림자 렉트

	POINT frameNum;	//프레임 숫자

	animation* ani;	//애니메이션
};

class z_order : public gameNode
{
private:

	object* obj;				// 벡터 삽입용 오브젝트
	vector<object*> vObj;		// Z_ORDER 용 오브젝트 벡터

private:

	//벡터 초기화
	void vClear() { vObj.clear(); }

public:

	virtual HRESULT init();		//초기화 함수
	virtual void release();		//메모리 해제 함슈
	virtual void update();		//연산하는 함수
	virtual void render();		//그리기 함수

	void pushObject(vector<enemy*> vem);
	void pushObject(player* pl);
	void pushObject(itemManager* im);

	//합병 정렬
	void merge(int left, int right);
	//정렬
	void mergeSort(int left, int right);
};