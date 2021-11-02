#include "pch.h"
#include "event.h"
#include "player.h"

HRESULT event::init()
{
	mapLockImage(); //이미지 보관소

	//탑 사슬 이미지, 좌표
	chain[0]._img = IMAGEMANAGER->findImage("topChain");
	chain[0]._x = -1600;
	chain[0]._y = 0;

	//바텀 사슬 이미지, 좌표
	chain[1]._img = IMAGEMANAGER->findImage("bottomChain");
	chain[1]._x = WINSIZEX;
	chain[1]._y = WINSIZEY - 43;

	//왼 사슬 이미지, 좌표
	chain[2]._img = IMAGEMANAGER->findImage("leftChain");
	chain[2]._x = 0;
	chain[2]._y = WINSIZEY;

	//오른 사슬 이미지, 좌표
	chain[3]._img = IMAGEMANAGER->findImage("rightChain");
	chain[3]._x = WINSIZEX - 41;
	chain[3]._y = WINSIZEY;

	//자물쇠 이미지, 렉트
	_lockImg = IMAGEMANAGER->findImage("lockIdle");
	_lockRc = RectMakeCenter(WINSIZEX / 2 - 5, 78, _lockImg->getFrameWidth(), _lockImg->getFrameHeight());

	//사슬 렉트, 불값
	for (int i = 0; i < 4; i++)
	{
		chain[i]._rc = RectMake(chain[i]._x, chain[i]._y, chain[i]._img->getWidth(), chain[i]._img->getHeight());
		chain[i]._isCheck = false;
	}
	//사슬 움직임, 자물쇠 불값 초기화
	_isShakingCount = 0;
	_isLockCheck = _isLastChange = _isStop = false;

	//대화 스크립트
	scriptImage = IMAGEMANAGER->findImage("dialog");
	scriptSkip = IMAGEMANAGER->findImage("skip");
	scriptSkip = IMAGEMANAGER->findImage("skip2");
	_vScript = TXTDATA->txtLoad("doit.txt");
	kScript = IMAGEMANAGER->findImage("kyoko");
	mScript = IMAGEMANAGER->findImage("misuzu");
	pName = IMAGEMANAGER->findImage("pName");
	eName = IMAGEMANAGER->findImage("eName");

	scriptStart = false;
	scriptEnd = true;
	_scriptSkip = false;

	scriptRc = RectMakeCenter(WINSIZEX / 2, 610, scriptImage->getWidth(), scriptImage->getHeight());

	_scriptIndex = _txtIndex = 0;
	return S_OK;
}

void event::release()
{
}

void event::update()
{
	//f5 누르면 ~ㄴ
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		_isLockCheck = true;
	}
	if (_isLockCheck == true)
	{
		if (_isShakingCount < 30)_isShakingCount++;

		for (int i = 0; i < 4; i++)
		{
			//체인 속도조절
			if (chain[0]._isCheck == false) chain[0]._x += 13;
			if (chain[1]._isCheck == false) chain[1]._x -= 13;
			if (chain[2]._isCheck == false) chain[2]._y -= 10;
			if (chain[3]._isCheck == false) chain[3]._y -= 10;
			
			//체인 흔들림 조절
			if (chain[0]._rc.right >= WINSIZEX)
			{
				chain[0]._isCheck = true;
				if (_isShakingCount < 30)
				{
					chain[0]._y += 3;
				}
				if (chain[0]._y >= 9)
				{
					chain[0]._y = 0;
				}
				
			}
			if (chain[1]._rc.left <= 0)
			{
				chain[1]._isCheck = true;
				if (_isShakingCount < 30)
				{
					chain[1]._y -= 3;
				}
				if (chain[1]._y <= WINSIZEY - 52)
				{
					chain[1]._y = WINSIZEY - 43;
				}
				
			}
			if (chain[2]._rc.top < 0)
			{
				chain[2]._isCheck = true;
				if (_isShakingCount < 30)
				{
					chain[2]._x += 3;
				}
				if (chain[2]._x >= 9)
				{
					chain[2]._x = 0;
				}
				

			}
			if (chain[3]._rc.top < 0)
			{
				chain[3]._isCheck = true;
				if (_isShakingCount < 30)
				{
					chain[3]._x -= 3;
				}
				if (chain[3]._x <= WINSIZEX - 50)
				{
					chain[3]._x = WINSIZEX - 41;
				}
				chain[3]._isCheck = true;
			}
		}
		//'A'를 누르면 자물쇠 흔들림
		frameCount();

		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_lockMovingCount = 0;
			_lockIndex = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('W') || _vem.size() == 2)
		{
			_lockImg = IMAGEMANAGER->findImage("lockChange1");
			_lockMovingCount = 0;
			_lockIndex = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('E') || _vem.size() == 1)
		{
			_lockImg = IMAGEMANAGER->findImage("lockChange2");
			_lockMovingCount = 0;
			_lockIndex = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('R') || _vem.size() == 0)
		{
			_lockImg = IMAGEMANAGER->findImage("lockChange3");
			_lockMovingCount = 0;
			_lockIndex++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_isStop = true;
		
	}
	if (_isStop == true)
	{
		if (_isStop && !scriptStart && scriptEnd)
		{
			scriptStart = true;
			scriptEnd = false;
		}
		if (!_scriptSkip)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
				_scriptSkip = true;
		}
		if (_scriptSkip)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
				_scriptSkip = false;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		chain[i]._rc = RectMake(chain[i]._x, chain[i]._y, chain[i]._img->getWidth(), chain[i]._img->getHeight());
	}
}

void event::render()
{
	//체인 랜더
	for (int i = 0; i < 4; i++)
	{
		if (_isLockCheck == true && _isLastChange == false)
		{
			chain[i]._img->render(getMemDC(), chain[i]._rc.left, chain[i]._rc.top);
			//Rectangle(getMemDC(), chain[i]._rc);
		}
	}
	//자물쇠 프레임 랜더
	if (_isLockCheck == true && _isLastChange == false)
	{
		_lockImg->frameRender(getMemDC(), _lockRc.left, _lockRc.top);
	}
	//대화 이벤트 시작
	if (scriptStart && !scriptEnd)
	{
		
		scriptImage->render(getMemDC(), scriptRc.left, scriptRc.top);
		scriptSkip->render(getMemDC(), 800, 10);
		scriptPlay();

		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		RECT rcText = RectMakeCenter(WINSIZEX/2 + 60, 650, 800, 150);
		//Rectangle(getMemDC(), rcText);
		HFONT font2 = CreateFont(21, 0, 0, 0, 500, false, false, false,
			HANGUL_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("바탕"));
		

		HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);

		DrawText(getMemDC(), TEXT(_txt.c_str()), _txtIndex, &rcText, DT_LEFT | DT_VCENTER | DT_WORDBREAK);

		SelectObject(getMemDC(), oldFont2);
		DeleteObject(font2);
	}

	//char str[128];
	//sprintf_s(str, "scriptEnd = %d", scriptEnd);
	//TextOut(getMemDC(), 500, 500, str, strlen(str));
	
}

void event::mapLockImage()
{
	//이미지 보관소
	IMAGEMANAGER->addImage("topChain", "image/ui/battle/Stage_UI_Chain_Top.bmp",
		1600, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bottomChain", "image/ui/battle/Stage_UI_Chain_Bottom.bmp",
		1600, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("leftChain", "image/ui/battle/Stage_UI_Chain_Left.bmp",
		42, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rightChain", "image/ui/battle/Stage_UI_Chain_Right.bmp",
		41, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lockIdle", "image/ui/battle/Stage_UI_Lock_Appear.bmp",
		650, 116, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lockChange1", "image/ui/battle/Stage_UI_Lock_Damage1.bmp",
		650, 116, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lockChange2", "image/ui/battle/Stage_UI_Lock_Damage2.bmp",
		650, 116, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lockChange3", "image/ui/battle/Stage_UI_Lock_Disappear.bmp",
		840, 130, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dialog", "image/ui/scene/dialogWindow.bmp", 1280, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("kyoko", "image/ui/scene/kyoko_1.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("misuzu", "image/ui/scene/misuzu_1.bmp", 386, 460, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skip", "image/ui/scene/UI_skip_outlines_WHITE.bmp", 206, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skip2", "image/ui/scene/UI_skip_outlines_FULL.bmp", 206, 78, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pName", "image/ui/scene/kyoko_name.bmp", 200, 76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("eName", "image/ui/scene/misuzu_name.bmp", 200, 76, true, RGB(255, 0, 255));

}

void event::frameCount()
{
	//자물쇠 움직임 코드
	if (_lockIndex <= _lockImg->getMaxFrameX())
	{
		_lockMovingCount++;
		if (_lockImg == IMAGEMANAGER->findImage("lockChange3") && _lockImg->getMaxFrameX() <= _lockIndex)
		{
			_isLastChange = true;
		}
	}

	if (_lockMovingCount % 10 == 0)
	{
		_lockImg->setFrameY(0);
		_lockImg->setFrameX(_lockIndex);
		_lockIndex++;
	}
}

void event::scriptPlay()
{
	_txt = _vScript[_scriptIndex];

	if (_scriptIndex == 0 || _scriptIndex == 1 || _scriptIndex == 3 || _scriptIndex == 5 || _scriptIndex == 7 || _scriptIndex == 9 || _scriptIndex == 10 || _scriptIndex == 11)
	{
		kScript->render(getMemDC(), 0, 75);
		pName->render(getMemDC(), 0, 572);
	}

	if (_scriptIndex == 2 || _scriptIndex == 4 || _scriptIndex == 6 || _scriptIndex == 8 || _scriptIndex == 12)
	{
		mScript->render(getMemDC(), 650, 75);
		eName->render(getMemDC(), 0, 572);
	}

	if (_scriptIndex > 12 || _scriptIndex >= _vScript.size())
	{
		scriptStart = false;
		scriptEnd = true;
		_isStop = false;
	}
	else if (!_scriptSkip) {
		scriptSkip = IMAGEMANAGER->findImage("skip");
		if (_txtIndex <= _txt.length())
		{
			_txtIndex++;
		}
		else if (_txtIndex >= _txt.length())
		{
			_scriptIndex++;

			_txtIndex = 0;

			Sleep(700);
		}
	}
	else if (_scriptSkip)
	{
		scriptSkip = IMAGEMANAGER->findImage("skip2");
		if (_txtIndex >= _txt.length())
		{
			_scriptIndex++;
			_txtIndex = 0;

			Sleep(200);
		}
		if (_txtIndex < _txt.length())
		{
			_txtIndex = _txt.length();
		}
	}
}

