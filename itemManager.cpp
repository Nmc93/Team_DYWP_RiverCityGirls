#include "pch.h"
#include "itemManager.h"
#include "gameNode.h"



itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}



HRESULT itemManager::init()
{



	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	for (int i = 0; i < vBat.size(); i++)
	{
		vBat[i]->update();
	}

	for (int i = 0; i < vFood.size(); i++)
	{
		vFood[i]->update();
	}

	for (int i = 0; i < vMoney.size(); i++)
	{
		vMoney[i]->update();
	}
}


void itemManager::dropBat(POINT ptxy)
{
	_bat = new bat;

	_bat->init(ptxy);
	vBat.push_back(_bat);

}

void itemManager::dropFood(FOODSTATE st, POINT ptxy)
{

	_food = new food;

	_food->init(st, ptxy);
	vFood.push_back(_food);
}

void itemManager::dropMoney(MONEYSTATE st, POINT ptxy)
{
	_money = new money;

	_money->init(st, ptxy);
	vMoney.push_back(_money);
}





void itemManager::render()
{
	for (int i = 0; i < vBat.size(); i++)
	{
		vBat[i]->render();
	}


	for (int i = 0; i < vFood.size(); i++)
	{
		vFood[i]->render();
	}
	
	for (int i = 0; i < vMoney.size(); i++)
	{
		vMoney[i]->render();
	}

}


