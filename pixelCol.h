#pragma once
#include "gameNode.h"
#include "camera.h"

class stageManager;

class pixelCol : public gameNode
{
private:
	stageManager* _sM;
	camera* _cam;

	bool _isMove;

	int r, g, b;

	//렉트 중심
	int _x, _y;
	RECT _rc;

public:
	HRESULT init(RECT rc);
	void release();
	void update(RECT rc);
	void render();

	bool getIsMove() { return _isMove; }

	void setStageManager (stageManager* sm) { _sM = sm; }
	void setCamera(camera* cam) { _cam = cam; }

};

