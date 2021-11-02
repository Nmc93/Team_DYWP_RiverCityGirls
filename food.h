#pragma once
#include "gameNode.h"
#include "imageManager.h"


enum FOODSTATE
{
	APPLE,
	HEN,
	CHILI
};



class food : public gameNode
{

private:

	float _jumpPower;
	float _gravity;

	bool _isJump;

	float x, y;
	int _sX, _sY;

	image* img;
	RECT RC;

	FOODSTATE state;


public:
	food();
	~food();

	virtual HRESULT init(FOODSTATE st, POINT ptxy);
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();

};