#pragma once
#include "gameNode.h"
#include "camera.h"

#define REAACTIONDISTANCE 10	// ��ǥ�� �Ÿ�
#define WARKSPEED 2				// �̵� �ӵ�
#define RANGE 120				// �÷��̾�� ���� �����Ÿ�

#define ATTRANGE 50				//�÷��̾�� ���� ��Ÿ�

#define GRAVITY 0.5f			//�߷�

//�̹��� Ÿ��
enum iStateType
{
	SCHOOLGIRL,
	SCHOOLBOY,
	CHEERLEADER,
	BOSS
};

//�ൿ Ÿ��
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

//������ ��¦
enum Lr
{
	ERIGHT,
	ELEFT
};
class enemy : public gameNode
{
private:
	
	camera* _cam;		//ī�޶�

	//���� Ÿ�̸�
	int _actTimer;		//���� Ÿ�̸�
	int _maxActTimer;	//���� ���� �ð�

	//���ʹ� Ÿ��
	iStateType iType;	// �̹��� Ÿ��
	aStateType aType;	// �ൿ Ÿ��
	Lr lr;				// �¿�

	// ������
	image* _shadowImg;	// �׸��� �̹���
	float _sX, _sY;		// �׸��� ���� ��ǥ
	RECT _shadowRc;		// �׸��� ��Ʈ
	float _speed;		// �¿� �̵� ���ǵ�

	// ����
	image* _img;		//���� �̹���
	float _bX, _bY;		//���� ������ǥ
	RECT _bodyRc;		//���� ��Ʈ
	
	float _rX, _rY;		//���� ��ǥ
	
	//���� ����
	bool _isJump;		//���� bool��
	float _jumpPower;	//���� �Ŀ���ġ

	//�̹��� ������ ����
	int count[2];		//�̹��� ������ ���� ī��Ʈ(0 : ī��Ʈ ,1 : 0�� �ִ�ġ)
	POINT frameNum;		//�̹��� ������ ��ȣ

	POINT _playerPosition;	//�÷��̾� ��ġ Ȯ�ο�
	float _angle;				//�� �̵��� �ޱ�

	//��Ʈ�ڽ�
	POINT hitBoxWH;		//��Ʈ�ڽ� ���� ����ũ��
	RECT hitBox;		//��Ʈ�ڽ� ��Ʈ
	bool hit;			//�ǰ� Ȯ��
	bool die;			//��� Ȯ��
	//bool hCount;		//���� �ǰ� ����
	int hitNum;			//�ǰ� ����(0 : �ȸ���, 1 : ���� ����, 2 : �ٿ� ����)

	//���� ����
	POINT attBoxWH;		//���� ���� ���� ����ũ��
	POINT attBoxXY;		//���� ���� ��ǥ ����
	RECT attBox;		//���� ���� ��Ʈ
	int attNum;			//���� ����(0 : �ȸ���, 1 : ���� ����, 2 : �ٿ� ����)
	bool attack;		//���� Ȯ��
	int _skillSize;		//y üũ ����
	int hp;				//ü��

	bool _check;		//Ư�� ���� Ȯ��

	//�ȼ��浹
	image* _pixelImage;	//�ȼ� �̹���

	//�׽�Ʈ
	int testInt;

private: // �Լ�

	void frameChange();	//������ ����
	void imageChange();	//Ÿ�Կ� ���� �̹��� ��ȯ
	void ai();			// AI �ൿ ����
	void bossAi();		// ���� AI �ൿ ����
	float enemyJump(float by);	//�� ����(Y��)
	void boxChange();	// �ൿ�� ���� ��Ʈ�ڽ� �� ���� ���� ��ȭ
	bool pixelColl(int r, int g, int b);	//�ȼ� �浹

	void Collision();	//�浹üũ

public:

	virtual HRESULT init(iStateType itype, POINT pt); //(���ʹ� ����,�� ���� ��ġ)
	virtual void release();
	virtual void update();
	virtual void render();

	//�ǰ� üũ(���� Ÿ��,�÷��̾� ��Ʈ ����, ���� Ÿ�� , y��, y�� �˻� ����)
	void setHit(bool att, RECT arc, int type, int sx, int sy, int ysize);

	// �÷��̾� ��ġ
	void setSpace(POINT pPosition) { _playerPosition = { pPosition.x,pPosition.y}; }

	image* getSImage() { return _shadowImg; }	// �׸��� �̹���
	image* getImage() { return _img; }			// ���� �̹���

	float getSX() { return _sX; }									//�׸��� x������ǥ
	float getSY() { return _sY; }									//�׸��� y������ǥ
	float getBX() { return _bX; }									//���� x������ǥ
	float getBY() { return _bY; }									//���� y������ǥ
	RECT getSRc() { return _shadowRc; }								//�׸��� ��Ʈ
	RECT getBRc() { return _bodyRc; }								//���� ��Ʈ
	POINT getFrame() { return frameNum; }							//���� y������ǥ
	int getSize() { return _skillSize; }		// yüũ ����

	bool getDie() { if (hp < 0 && _actTimer >= 170) return true; else return false;}	//��� Ȯ��

	void setCam(camera* cam) { _cam = cam; } //ī�޶� �޾ƿ���
	void setPixel(image* pixelimage) { _pixelImage = pixelimage; }	//�ȼ� �̹��� �޾ƿ���
	
    //														
																	
	// �÷��̾� ��������� ���� Jo
	int getAttNum() { return attNum; }		//���� Ÿ��
	RECT getAtkBox() { return attBox; }
	bool getAttAck() { return attack; }
	int getAType() { return aType; }

	iStateType getIType() { return iType; }
};