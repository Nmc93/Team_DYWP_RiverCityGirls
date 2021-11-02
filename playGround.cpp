#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);
	
	//IMAGEMANAGER->addImage("배경","stage.bmp", WINSIZEX * 1.5, WINSIZEY, true, RGB(255, 0, 255));

	//_p = new player;
	//_p->init();

	//_cam = new camera;
	//_cam->init();

	//_p = new player;

	// 카메라 연결
	//_p->setCamera(_cam);

	//_p->init();

	//스테이지 매니저
	_sM = new stageManager;
	_sM->init();

	//지우지 말아주세요! 아이템!
	_itemMG = new itemManager;
	_itemMG->init();
  
	_itemMG->dropBat({ 400, 400 });
	_itemMG->dropBat({ 800, 400 });
	_itemMG->dropFood(APPLE, { 400, 600 });
	_itemMG->dropMoney(COIN, { 600, 600 });
	_itemMG->dropMoney(BILL, { 800, 600 });

	_zO = new z_order;
	_zO->init();
	_zO->pushObject(_sM->getPlayer());
	_zO->pushObject(_sM->getEnemyVector());

	return S_OK;
}

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();
}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	//스테이지 매니저
	if(!_sM->getEvent()->getIsStop()) _sM->update();
	

	//_p->update();

	//지우지 말아주세요! 아이템!
	_itemMG->update();

	//zorder -> 플레이어 및 에너미
	_zO->pushObject(_sM->getPlayer());
	_zO->pushObject(_sM->getEnemyVector());
	//zorder 업데이트
	_zO->update();
	
	
}

//여기다 그려줘라!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============위에는 제발 건드리지 마라 ============
	
	//IMAGEMANAGER->findImage("배경")->render(getMemDC());
	//_cam->render();
	_sM->render();
	_zO->render();
	_sM->getEvent()->render();
	//_p->render();

	//지우지 말아주세요! 아이템!
	//_itemMG->render();
	
	if(KEYMANAGER->isToggleKey(VK_NUMPAD2)) TIMEMANAGER->render(getMemDC());

	//=============== 밑에도 건들지마라 ================
	_backBuffer->render(getHDC(), 0, 0);

}

