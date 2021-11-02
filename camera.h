#pragma once
#include "gameNode.h"
#include <vector>


class camera : public gameNode
{
private:
	//RECT _rc;
	int _x, _y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void stageStart();
	void nomalStage();
	void bossStage();

	

	float getX() { return _x; }
	void setX(int x) { _x = x; }

	float getY() { return _y; }
	void setY(int y) { _y = y; }

	
};


