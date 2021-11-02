#pragma once
#include "gameNode.h"
#include <string>
#include "enemy.h"
#include <vector>

struct tagEvent
{
	float _x, _y;				//��罽 ��ǥ
	RECT _rc;					//��罽 ��Ʈ
	image* _img;				//��罽 �̹���			
	bool _isCheck;				//��罽 ��ȣ bool ��

};

class event : public gameNode
{
private:
	
	//�� ��� �̺�Ʈ ������

	tagEvent chain[4];						//��罽 ����ü �迭
	int _isShakingCount, _lockMovingCount;  //��罽 ��鸲, �ڹ��� ��鸲 ī��Ʈ ����
	RECT _lockRc;							//�ڹ��� ��Ʈ
	image* _lockImg;						//�ڹ��� �̹���

	int _lockIndex;							//�ڹ��� ������ �ε���
	bool _isLockCheck;						//�ڹ��� bool ��
	bool _isLastChange;						//�ڹ��� ������ ��ȭ
	bool _isStop;
	//��ȭ ������

	bool scriptStart;						//��ũ��Ʈ ����
	bool scriptEnd;							//��ũ��Ʈ ��
	RECT scriptRc;							//��ũ��Ʈ ��Ʈ(����ȭ��)
	image* scriptImage;						//��ũ��Ʈ �̹���
	int _scriptIndex;						//��ũ��Ʈ �迭 �ε���
	int _txtIndex;							//�ؽ�Ʈ ���� ���ڼ�
	vector<string> _vScript;				//��ũ��Ʈ �迭 ����
	string _txt;							//�ؽ�Ʈ ����
	image* scriptSkip;						//��ũ��Ʈ ��ŵ �̹���
	bool _scriptSkip;						//��ũ��Ʈ ��ŵ bool ��

	image* kScript;							//�÷��̾� �̹���
	image* mScript;							//�� �̹���

	image* pName;							//��ũ��Ʈ ���� �̹��� �̸� (�÷��̾�)
	image* eName;							//��ũ��Ʈ ���� �̹��� �̸� (����)

	vector<enemy*> _vem;		//��ῡ ���� ����

public:
	virtual HRESULT init();					//�ʱ�ȭ �Լ�
	virtual void release();					//�޸� ���� �Խ�
	virtual void update();					//�����ϴ� �Լ�
	virtual void render();					//�׸��� �Լ�


	void mapLockImage();					//�ʿ� �̹��� �Լ�
	void frameCount();						//������ ī��Ʈ �Լ�
	void scriptPlay();						//��ũ��Ʈ �÷��� �Լ�

	bool getIsScriptStart() { return scriptStart; }	//��ũ��Ʈ ��ŸƮ bool
	bool getIsScriptEnd() { return scriptEnd; }	//��ũ��Ʈ ���� bool
	bool getIsLock() { return _isLockCheck; } //�� ��� bool ��
	bool getIsStop() { return _isStop; }	//��ũ��Ʈ �߻��� ���� ���� bool ��
	bool getIsLastChange() { return _isLastChange; }//�ڹ��� ������ ī�޶� �����̰����ִ� bool ��

	void setIsLock(bool isLockCheck) { _isLockCheck = isLockCheck; } // �ڹ��� ��� ����
	void setIsStop(bool isStop) { _isStop = isStop; }				 // ��ũ��Ʈ ��� ����
	void setIsScriptEnd(bool isScriptEnd) { scriptEnd = isScriptEnd; } //��ũ��Ʈ ���� ����
	void setIsScriptStart(bool isScriptStart) { scriptStart = isScriptStart; }//��ũ��Ʈ ��ŸƮ ����

	void setEnemy(vector<enemy*> vem) { _vem = vem; }
};