#pragma once
#include "gameNode.h"
#include <string>
#include "enemy.h"
#include <vector>

struct tagEvent
{
	float _x, _y;				//쇠사슬 좌표
	RECT _rc;					//쇠사슬 렉트
	image* _img;				//쇠사슬 이미지			
	bool _isCheck;				//쇠사슬 신호 bool 값

};

class event : public gameNode
{
private:
	
	//맵 잠김 이벤트 변수들

	tagEvent chain[4];						//쇠사슬 구조체 배열
	int _isShakingCount, _lockMovingCount;  //쇠사슬 흔들림, 자물쇠 흔들림 카운트 변수
	RECT _lockRc;							//자물쇠 렉트
	image* _lockImg;						//자물쇠 이미지

	int _lockIndex;							//자물쇠 프레임 인덱스
	bool _isLockCheck;						//자물쇠 bool 값
	bool _isLastChange;						//자물쇠 마지막 변화
	bool _isStop;
	//대화 변수들

	bool scriptStart;						//스크립트 시작
	bool scriptEnd;							//스크립트 끝
	RECT scriptRc;							//스크립트 렉트(검은화면)
	image* scriptImage;						//스크립트 이미지
	int _scriptIndex;						//스크립트 배열 인덱스
	int _txtIndex;							//텍스트 파일 글자수
	vector<string> _vScript;				//스크립트 배열 벡터
	string _txt;							//텍스트 파일
	image* scriptSkip;						//스크립트 스킵 이미지
	bool _scriptSkip;						//스크립트 스킵 bool 값

	image* kScript;							//플레이어 이미지
	image* mScript;							//적 이미지

	image* pName;							//스크립트 왼쪽 이미지 이름 (플레이어)
	image* eName;							//스크립트 왼쪽 이미지 이름 (보스)

	vector<enemy*> _vem;		//잠결에 만든 벡터

public:
	virtual HRESULT init();					//초기화 함수
	virtual void release();					//메모리 해제 함슈
	virtual void update();					//연산하는 함수
	virtual void render();					//그리기 함수


	void mapLockImage();					//필요 이미지 함수
	void frameCount();						//프레임 카운트 함수
	void scriptPlay();						//스크립트 플레이 함수

	bool getIsScriptStart() { return scriptStart; }	//스크립트 스타트 bool
	bool getIsScriptEnd() { return scriptEnd; }	//스크립트 엔드 bool
	bool getIsLock() { return _isLockCheck; } //맵 잠김 bool 값
	bool getIsStop() { return _isStop; }	//스크립트 발생시 게임 멈춤 bool 값
	bool getIsLastChange() { return _isLastChange; }//자물쇠 깨지면 카메라 움직이게해주는 bool 값

	void setIsLock(bool isLockCheck) { _isLockCheck = isLockCheck; } // 자물쇠 잠김 세터
	void setIsStop(bool isStop) { _isStop = isStop; }				 // 스크립트 잠김 세터
	void setIsScriptEnd(bool isScriptEnd) { scriptEnd = isScriptEnd; } //스크립트 엔드 세터
	void setIsScriptStart(bool isScriptStart) { scriptStart = isScriptStart; }//스크립트 스타트 세터

	void setEnemy(vector<enemy*> vem) { _vem = vem; }
};