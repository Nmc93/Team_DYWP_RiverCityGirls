#pragma once
#include "state.h"
class wBatRun : public state
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void stateChange();
	virtual void setAni();

};

