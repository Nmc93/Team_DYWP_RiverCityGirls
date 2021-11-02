#pragma once
#include "gameNode.h"
#include "imageManager.h"

enum class WEAPONSTATE
{
	RIGHT_IDLE,
	LEFT_IDLE
};

class bat : public gameNode
{

private:

	image* _idle;

	image* _batImage;
	RECT _batRC;
	WEAPONSTATE state;

	float x, y;
	int _width, _height;

	float _jumpPower;
	float _gravity;

	bool _isJump;
	bool _isGo;

	int _sX, _sY;
	int speed;
	int count;

public:
	bat();
	~bat();

	virtual HRESULT init(POINT ptxy);
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();
	void goBat(WEAPONSTATE st, POINT ptxy);
};

