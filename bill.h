#pragma once
#include "gameNode.h"
#include "money.h"


class bill : public gameNode
{

private:



public:
	bill();
	~bill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void drop();

};


