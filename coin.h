#pragma once
#include "gameNode.h"
#include "money.h"



class coin : public gameNode
{

private:

	image* _coin;
	animation* _coinMotion;

	int _count;
	int _indexX;

public:
	coin();
	~coin();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();

};


