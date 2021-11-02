#pragma once
#include "gameNode.h"

#include "bat.h"
#include "food.h"
#include "money.h"
#include <vector>

#define GRAVITY 1.0f

class itemManager : public gameNode
{


private:
	vector <bat*> vBat;
	vector <food*> vFood;
	vector <money*> vMoney;




	bat* _bat;

	food* _food;

	money* _money;

	float jumpPower;


public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void dropBat(POINT ptxy);
	void dropFood(FOODSTATE st, POINT ptxy);
	void dropMoney(MONEYSTATE st, POINT ptxy);
};



