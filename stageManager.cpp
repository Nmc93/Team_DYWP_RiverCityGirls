#include "pch.h"
#include "stageManager.h"
#include "stageData.h"

HRESULT stageManager::init()
{
    //스테이지 데이터
    sData = new stageData;
    sData->init();

    //카메라
    _cam = new camera;
    _cam->init();
  
    // 첫 화면
    _img = IMAGEMANAGER->findImage("BACKGROUND");
    _pixelImg = IMAGEMANAGER->findImage("BACKGROUNDP");
  
    createEnemy(1);

    //플레이어
    _p = new player;
    _p->setCamera(_cam);
    _p->init();
    _p->getPC()->setStageManager(this);

    _p->setBImg(_img);

    
    //이벤트
    _ev = new event;
    _ev->init();
  
    _isCount = 0;
    _isCheck = false;
    _isDelete = false;
    _eventBool = false;
    _eventCount = 0;
    
    return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
    // 플레이어 추가
    _p->getState()->setVEnemy(_vem);
    _p->getState()->setEnemy(_em);
    _p->setBImg(_img);
    //플레이어 업데이트
    _p->update();
    
    //에너미 업데이트
    for (int i = 0; i < _vem.size(); i++)
    {

        //_p->getAtk()
        _vem[i]->setHit(_p->getAtk(), _p->getAtkBox(), _p->getType(), _p->getSX(), _p->getSY(), 30);
        //if(KEYMANAGER->isOnceKeyDown(VK_NUMPAD0)) _vem[i]->setHit(true, _vem[i]->getBRc(),2, _vem[i]->getSY(),40);
        _vem[i]->setSpace({ _p->getSX() , _p->getSY() });
        _vem[i]->setPixel(_pixelImg);
        _vem[i]->update();

    }

    deleteEnemy(0);
    //===========================================================================================
    //==============================   이벤트   =================================================
    //===========================================================================================

    if(_isCount == 0 && _isCheck == false)
    {
        _img = IMAGEMANAGER->findImage("BACKGROUND");
        _pixelImg = IMAGEMANAGER->findImage("BACKGROUNDP");

        stage._d = WINSIZEX / 2 + 820;							                              
        stage._f = WINSIZEY / 2 - 20;							                              
        stage._rc1 = RectMake(stage._d - _cam->getX(), stage._f - _cam->getY(), 220, 100);	  
        stage._rc2 = RectMake(1, 1, 1, 1);
       
    }
     
    if (_isCount == 1 && _isCheck == false)
    {
       
        _img = IMAGEMANAGER->findImage("BACKGROUND1");
        _pixelImg = IMAGEMANAGER->findImage("BACKGROUNDP1");

         stage._d = 0;
        stage._f = 570;
        stage._d1 = 2600;
        stage._f1 = 500;
        stage._rc1 = RectMake(stage._d - _cam->getX(), stage._f - _cam->getY(), 150, 150);
        stage._rc2 = RectMake(stage._d1 - _cam->getX(), stage._f1 - _cam->getY(), 150, 150);
        stage._rc3 = RectMake(2250 - _cam->getX(), 400 - _cam->getY(), 50, 280);
    }

    if (_isCount == 2 && _isCheck == false)
    { 
        _img = IMAGEMANAGER->findImage("BACKGROUND2");
        _pixelImg = IMAGEMANAGER->findImage("BACKGROUNDP2");

        stage._d = 50;
        stage._f = 400;
        stage._rc1 = RectMake(stage._d - _cam->getX(), stage._f - _cam->getY(), 150, 150);
        stage._rc2 = RectMake(1, 1, 1, 1);
        stage._rc3 = RectMake(800 - _cam->getX(), 200 - _cam->getY(), 50, 500);
    }
    //충돌처리
    RECT temp;
    RECT pRc;
    pRc = _p->getSRc();

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {

        if (IntersectRect(&temp, &stage._rc1, &pRc) && _isCount == 0 && _p->getIsCameraLock() == false)
        {
            deleteEnemy(1);
            createEnemy(2);
            _cam->setX(0);
            _cam->setY(0);
            _isCount = 1;
            _p->setSX(150);
            _p->setSY(650);
            return;
        }

        if (IntersectRect(&temp, &stage._rc2, &pRc) && _isCount == 1 && _p->getIsCameraLock() == false)
        {
            deleteEnemy(1);
            _cam->setX(0);
            _isCount = 2;
            _p->setSX(130);
            _p->setSY(520);
            return;
           
        }
        if (IntersectRect(&temp, &stage._rc1, &pRc) && _isCount == 1 && _p->getIsCameraLock() == false)
        {
            deleteEnemy(1);
            createEnemy(1);
            _cam->setX(900);
            _cam->setY(0);
            _isCount = 0;
            _p->setSX(WINSIZEX/2);
            _p->setSY(400);
            return;
           
        }
        if (IntersectRect(&temp, &stage._rc1, &pRc) && _isCount == 2 && _p->getIsCameraLock() == false)
        {
            deleteEnemy(1);
            createEnemy(2);
            _cam->setX(IMAGEMANAGER->findImage("BACKGROUND1")->getWidth() - WINSIZEX);
            _isCount = 1;
            _p->setSX(WINSIZEX-200);
            _p->setSY(650);
            return;
          
        }
    }
    // 맵 잠김
    if (IntersectRect(&temp, &stage._rc3, &pRc) && _isCount == 1 && !_eventBool)
    {
        createEnemy(2);
        _eventBool = true;
        _ev->setIsLock(true);
        _p->setIsCameraLock(true);
    }
    if (_ev->getIsLastChange() == true)
    {
        _p->setIsCameraLock(false);
    }
    // 스크립트 시작
    if (IntersectRect(&temp, &stage._rc3, &pRc) && _isCount == 2 && !_isDelete)
    {
        createEnemy(3);
        _isDelete = true;
        if(_isDelete)stage._rc3 = RectMake(0, 0, 0, 0);
        _ev->setIsStop(true);
        _ev->setIsScriptEnd(false);
        _ev->setIsScriptStart(true);
    }
    //if (_ev->getIsStop() == false)
  
    //이벤트 업데이트
    _ev->update();
    _ev->setEnemy(_vem);
}

void stageManager::render()
{
    _img->render(getMemDC(), 0, 0, _cam->getX(), _cam->getY(), WINSIZEX, WINSIZEY);
   
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        _pixelImg->render(getMemDC(), 0, 0, _cam->getX(), _cam->getY(), WINSIZEX, WINSIZEY);
    }

    //플레이어 렌더
    _p->render();

    for (int i = 0; i < _vem.size(); i++)
    {
        _vem[i]->render();
    }

    //Rectangle(getMemDC(), stage._rc1);
    //Rectangle(getMemDC(), stage._rc2);
    //Rectangle(getMemDC(), stage._rc3);
   
    //이벤트 랜더
    //_ev->render();
  
    //char str[128];
    //sprintf_s(str, "_isCount = %d", _isCount);
    //TextOut(getMemDC(), 500, 0, str, strlen(str));

}

//몹 생성
void stageManager::createEnemy(int stage)
{
    if (stage == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            int j = RND->getInt(2);
            _em = new enemy;

            if (j == 0) _em->init(SCHOOLBOY, sData->getGen1(i));
            else if (j == 1) _em->init(SCHOOLGIRL, sData->getGen1(i));

            _em->setPixel(_pixelImg);
            _em->setCam(_cam);

            _vem.push_back(_em);
        }
    }
    else if (stage == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            int j = RND->getInt(2);
            _em = new enemy;

            if(j == 0) _em->init(SCHOOLBOY, sData->getGen2(i));
            else if (j == 1) _em->init(SCHOOLGIRL, sData->getGen2(i));

            _em->setPixel(_pixelImg);
            _em->setCam(_cam);

            _vem.push_back(_em);
        }
    }
    else if (stage == 3)
    {
        _em = new enemy;
        _em->init(BOSS, sData->getGen3(0));
        _em->setPixel(_pixelImg);
        _em->setCam(_cam);

        _vem.push_back(_em);
    }
}

//적 제거(0 : 체력적 제거, 1 : 전체 제거)
void stageManager::deleteEnemy(int num)
{
    if (num == 0)
    {
        for (int i = 0; i < _vem.size(); i++)
        {
            if (_vem[i]->getIType() != BOSS && _vem[i]->getDie()) _vem.erase((_vem.begin() + i));
        }
    }
    else if (num == 1)
    {
        vector<enemy*> vem;
        _vem.clear();
        _vem.swap(vem);
    }
}
