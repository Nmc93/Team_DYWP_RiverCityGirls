#pragma once
#include "state.h"

class atk : public state
{
private:
	int _atkCount;	// 공격 횟수
	int _timer;		// Idle로 돌아가는 시간

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void setAni();

	void cbFunction();
};

