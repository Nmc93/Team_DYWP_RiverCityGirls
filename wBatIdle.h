#pragma once
#include "state.h"
class wBatIdle : public state
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void setAni();

};

