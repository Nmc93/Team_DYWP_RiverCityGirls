#pragma once
#include "gameNode.h"

struct MyStruct
{

};

class stageData : public gameNode
{
private:

	POINT genStage1[2];				//�������� 1 �� ����Ʈ
	POINT genStage2[3];				//�������� 2 �� ����Ʈ
	POINT genStage3[1];				//�������� 3 �� ����Ʈ

	void createImage();				//�̹��� ����
	void createGenPoint();			//������Ʈ ����

public:

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	POINT getGen1(int num) { return genStage1[num]; }
	POINT getGen2(int num) { return genStage2[num]; }
	POINT getGen3(int num) { return genStage3[num]; }

};