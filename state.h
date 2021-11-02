#pragma once
#include "gameNode.h"
#include "animation.h"


#define GRAVITY 0.3f;

class player;
class enemy;

//왼쪽이냐 오른쪽이냐
enum dir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NORMAL
};

class state : public gameNode
{
protected:

	vector<enemy*> _vem;
	enemy* _e;

	image* _img;		// 나이트 이미지
	image* _pastImg;

	int _wDir, _hDir;   // 나이트 방향

	animation* _motion; // 나이트 모션

	double _jump = 10.0f; 

	player* _p;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange() {};
	virtual void setAni() {};
	virtual void findImage(const char* imageName);
	void col();

	virtual void setKnight(player* p) { _p = p; }

	virtual animation* getMotion() { return _motion; };
	virtual image* getImage() { return _img; }

	virtual image* getPastImage() { return _pastImg; }
	virtual void setPastImage(image* pastImg) { _pastImg = pastImg; }

	virtual float getJump() { return _jump; }

	animation* getAni() { return _motion; }

	void setVEnemy(vector<enemy*> vem) { _vem = vem; }
	void setEnemy(enemy* e) { _e = e; }
};

