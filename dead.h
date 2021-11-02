#pragma once
#include "state.h"
class dead : public state
{


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void setAni();
};

