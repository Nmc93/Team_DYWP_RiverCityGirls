#pragma once
#include "state.h"
class walk : public state
{
private:
	int _timer;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	virtual void stateChange();
	virtual void setAni();
	
};

