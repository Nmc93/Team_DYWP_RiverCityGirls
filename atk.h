#pragma once
#include "state.h"

class atk : public state
{
private:
	int _atkCount;	// ���� Ƚ��
	int _timer;		// Idle�� ���ư��� �ð�

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void setAni();

	void cbFunction();
};

