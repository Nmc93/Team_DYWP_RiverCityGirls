#pragma once
#include "gameNode.h"
#include "imageManager.h"

enum MONEYSTATE
{
	COIN,
	BILL
};


class money : public gameNode
{

private:

	float _jumpPower;
	float _gravity;

	bool _isJump;

	float x, y;
	int _sX, _sY;

	int _count;
	int _indexX;

	image* img;
	RECT RC;

	MONEYSTATE state;

public:
	money();
	~money();

	virtual HRESULT init(MONEYSTATE st, POINT ptxy);
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();
};


