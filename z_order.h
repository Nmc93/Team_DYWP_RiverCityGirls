#pragma once
#include"gameNode.h"
#include"stageManager.h"
#include"player.h"
#include"itemManager.h"
#include <vector>

enum kind	//������Ʈ Ű��
{
	PL,	//�÷��̾�
	EM,	//��
	IT	//������
};

struct object
{
	kind key;		//����
	image* img;		//�̹���
	image* sImg;	//�׸��� �̹���
	float bX, bY;	//���� ���� ��ǥ
	RECT bRc;		//���� ��Ʈ
	float sX, sY;	//�׸��� ���� ��ǥ
	RECT sRc;		//�׸��� ��Ʈ

	POINT frameNum;	//������ ����

	animation* ani;	//�ִϸ��̼�
};

class z_order : public gameNode
{
private:

	object* obj;				// ���� ���Կ� ������Ʈ
	vector<object*> vObj;		// Z_ORDER �� ������Ʈ ����

private:

	//���� �ʱ�ȭ
	void vClear() { vObj.clear(); }

public:

	virtual HRESULT init();		//�ʱ�ȭ �Լ�
	virtual void release();		//�޸� ���� �Խ�
	virtual void update();		//�����ϴ� �Լ�
	virtual void render();		//�׸��� �Լ�

	void pushObject(vector<enemy*> vem);
	void pushObject(player* pl);
	void pushObject(itemManager* im);

	//�պ� ����
	void merge(int left, int right);
	//����
	void mergeSort(int left, int right);
};