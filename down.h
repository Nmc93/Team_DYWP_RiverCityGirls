#pragma once
#include "state.h"
class down : public state
{
private:
	int _timer;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void setAni();
};

