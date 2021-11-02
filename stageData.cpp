#include "pch.h"
#include "stageData.h"

HRESULT stageData::init()
{
	createGenPoint();
	createImage();
	return S_OK;
}

void stageData::release()
{
}

void stageData::update()
{
}

void stageData::render()
{
}


//이미지 생성
void stageData::createImage()
{
	//스테이지
	IMAGEMANAGER->addImage("BACKGROUND", "image/stage/easy.bmp", 2028, 678, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BACKGROUNDP", "image/stage/easyPixel.bmp", 2028, 678, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("BACKGROUND1", "image/stage/normal.bmp", 2865, 837, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BACKGROUNDP1", "image/stage/normalPixel.bmp", 2865, 837, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("BACKGROUND2", "image/stage/boss2.bmp", WINSIZEX * 1.5, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BACKGROUNDP2", "image/stage/bossPixel.bmp", WINSIZEX * 1.5, WINSIZEY, true, RGB(255, 0, 255));

	//문
	IMAGEMANAGER->addImage("Door", "image/ui/UI_UnLocked_Door.bmp", 52, 76, true, RGB(255, 0, 255));
	
	
	//그림자
	IMAGEMANAGER->addImage("SHADOW", "shadow.bmp", 128, 39, true, RGB(255, 0, 255));

	//플레이어 
	IMAGEMANAGER->addFrameImage("P_IDLE", "image/character/player/idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WALK", "image/character/player/walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_RUN", "image/character/player/run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_JUMP", "image/character/player/jump.bmp", 480, 680, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK1", "image/character/player/comboAttack1.bmp", 1548, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK2", "image/character/player/comboAttack2.bmp", 1869, 402, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_COMBOATTACK3", "image/character/player/comboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_SATTACK", "image/character/player/strongAttack.bmp", 3030, 474, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DOWN", "image/character/player/down.bmp", 4968, 390, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_STAND", "image/character/player/stand.bmp", 1863, 450, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DASHATTACK", "image/character/player/dashAttack.bmp", 2565, 414, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GUARD", "image/character/player/guard.bmp", 351, 378, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DEAD", "image/character/player/dead.bmp", 7280, 478, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GRAB", "image/character/player/grab.bmp", 270, 384, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_GRABFAIL", "image/character/player/grabFail.bmp", 812, 422, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_PICK", "image/character/player/pick.bmp", 222, 450, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_HIT", "image/character/player/hit.bmp", 246, 420, 2, 2, true, RGB(255, 0, 255));

	// 방망이 상태
	IMAGEMANAGER->addFrameImage("P_WBATIDLE", "image/character/player/wBatIdle.bmp", 1440, 560, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATWALK", "image/character/player/wBatWalk.bmp", 1476, 500, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATRUN", "image/character/player/wBatRun.bmp", 6784, 560, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATJUMP", "image/character/player/wBatJump.bmp", 480, 680, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATATTACK", "image/character/player/wBatAttack.bmp", 1700, 700, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_WBATTHROW", "image/character/player/wBatThrow.bmp", 1616, 600, 8, 2, true, RGB(255, 0, 255));

	//====================================================================================================================================

	IMAGEMANAGER->addFrameImage("P_CLIMB", "image/character/player/climb.bmp", 720, 237, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_CLIMBTOP", "image/character/player/climbTop.bmp", 288, 192, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_CLIMBDOWN", "image/character/player/climbDown.bmp", 288, 234, 3, 1, true, RGB(255, 0, 255));

	//schoolGirl 이미지
	//대기,걷기,뛰기,점프(기본 행동)
	IMAGEMANAGER->addFrameImage("SG_IDLE", "image/character/enemy/schoolGirl/Idle.bmp", 1170, 354, 10, 2, true, RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("SG_WARK", "image/character/enemy/schoolGirl/walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_RUN", "image/character/enemy/schoolGirl/run.bmp", 1470, 330, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_JUMP", "image/character/enemy/schoolGirl/jump.bmp", 342, 366, 3, 2, true, RGB(255, 0, 255));

	//공격
	IMAGEMANAGER->addFrameImage("SG_ATT1", "image/character/enemy/schoolGirl/comboAttack1.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_ATT2", "image/character/enemy/schoolGirl/comboAttack2.bmp", 2208, 354, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_ATT3", "image/character/enemy/schoolGirl/comboAttack3.bmp", 2412, 414, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_JATT", "image/character/enemy/schoolGirl/jumpAttack.bmp", 1197, 354, 7, 2, true, RGB(255, 0, 255));

	//막기
	IMAGEMANAGER->addFrameImage("SG_BLOCK", "image/character/enemy/schoolGirl/block.bmp", 351, 338, 3, 2, true, RGB(255, 0, 255));

	//피격
	IMAGEMANAGER->addFrameImage("SG_HIT", "image/character/enemy/schoolGirl/HeldHit.bmp", 576, 336, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_DOWN", "image/character/enemy/schoolGirl/backdown.bmp", 6939, 376, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_STUN", "image/character/enemy/schoolGirl/stun.bmp", 456, 324, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_DIE", "image/character/enemy/schoolGirl/weapon_swing.bmp", 4369, 336, 17, 2, true, RGB(255, 0, 255));

	//무기 장착시
	IMAGEMANAGER->addFrameImage("SG_WIDLE", "image/character/enemy/schoolGirl/stun.bmp", 1950, 408, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_WWALK", "image/character/enemy/schoolGirl/WWalk.bmp", 2232, 502, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_WRUN", "image/character/enemy/schoolGirl/WRun.bmp", 1880, 458, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_WJUMP", "image/character/enemy/schoolGirl/WJump.bmp", 429, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_WATT", "image/character/enemy/schoolGirl/WAttack.bmp", 1580, 558, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_WTHROW", "image/character/enemy/schoolGirl/WThrow.bmp", 1488, 540, 8, 2, true, RGB(255, 0, 255));

	//schoolBoy 이미지
	//대기,걷기,뛰기,점프(기본 행동)
	IMAGEMANAGER->addFrameImage("SB_IDLE", "image/character/enemy/schoolBoy/Idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_WARK", "image/character/enemy/schoolBoy/walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_RUN", "image/character/enemy/schoolBoy/run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_JUMP", "image/character/enemy/schoolBoy/jump.bmp", 423, 486, 3, 2, true, RGB(255, 0, 255));

	//공격
	IMAGEMANAGER->addFrameImage("SB_ATT1", "image/character/enemy/schoolBoy/comboAttack1.bmp", 2352, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_ATT2", "image/character/enemy/schoolBoy/comboAttack2.bmp", 1757, 444, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_ATT3", "image/character/enemy/schoolBoy/comboAttack3.bmp", 1890, 558, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_JATT", "image/character/enemy/schoolBoy/jumpAttack.bmp", 1224, 468, 6, 2, true, RGB(255, 0, 255));

	//막기
	IMAGEMANAGER->addFrameImage("SB_BLOCK", "image/character/enemy/schoolBoy/block.bmp", 459, 438, 3, 2, true, RGB(255, 0, 255));

	//피격
	IMAGEMANAGER->addFrameImage("SB_HIT", "image/character/enemy/schoolBoy/HeldHit.bmp", 576, 372, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_DOWN", "image/character/enemy/schoolBoy/backdown.bmp", 7695, 438, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_STUN", "image/character/enemy/schoolBoy/stun.bmp", 633, 408, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_DIE", "image/character/enemy/schoolBoy/weapon_swing.bmp", 5415, 438, 19, 2, true, RGB(255, 0, 255));

	//Boss 이미지
	//대기,걷기
	IMAGEMANAGER->addFrameImage("BS_IDLE", "image/character/enemy/boss/idle.bmp", 3180, 634, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_WARK", "image/character/enemy/boss/walk.bmp", 2110, 588, 10, 2, true, RGB(255, 0, 255));

	//공격(엘보,로어,전진공격)
	IMAGEMANAGER->addFrameImage("BS_ATT1", "image/character/enemy/boss/elbow.bmp", 2915, 652, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_ROAR", "image/character/enemy/boss/roar.bmp", 2916, 576, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_SLAP", "image/character/enemy/boss/slap.bmp", 5278, 582, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_MATT", "image/character/enemy/boss/wupunch.bmp", 11880, 594, 27, 2, true, RGB(255, 0, 255));
	
	//공격(시작 돌진 돌진)
	IMAGEMANAGER->addFrameImage("BS_RUN", "image/character/enemy/boss/tackle.bmp", 1120, 576, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_DASH", "image/character/enemy/boss/dash.bmp", 2916, 582, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_RUSH", "image/character/enemy/boss/tackle_L.bmp", 2882, 576, 11, 2, true, RGB(255, 0, 255));

	//공격(점프 날아감 떨어짐 후딜레이)
	IMAGEMANAGER->addFrameImage("BS_JATT1", "image/character/enemy/boss/meteor_J.bmp", 1888, 672, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_JATT2", "image/character/enemy/boss/meteor_A.bmp", 410, 660, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_JATT3", "image/character/enemy/boss/meteor.bmp", 480, 460, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_JATT4", "image/character/enemy/boss/meteor_M.bmp", 4674, 576, 19, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("BS_DATT1", "image/character/enemy/boss/getup_S.bmp", 2560, 466, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_DATT2", "image/character/enemy/boss/getup_C.bmp", 2187, 576, 9, 2, true, RGB(255, 0, 255));

	//도발
	IMAGEMANAGER->addFrameImage("BS_TAUNT", "image/character/enemy/boss/taunt.bmp", 5658, 748, 23, 2, true, RGB(255, 0, 255));

	//피격
	IMAGEMANAGER->addFrameImage("BS_HIT1", "image/character/enemy/boss/attacked 01.bmp", 737, 594, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_HIT2", "image/character/enemy/boss/attacked 02.bmp", 737, 594, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_HIT3", "image/character/enemy/boss/attacked 03.bmp", 737, 598, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_DHIT", "image/character/enemy/boss/groundhit.bmp", 1036, 460, 4, 2, true, RGB(255, 0, 255));
	
	//사망
	IMAGEMANAGER->addFrameImage("BS_DIE", "image/character/enemy/boss/defeat.bmp", 4576, 576, 13, 2, true, RGB(255, 0, 255));

	//다운
	IMAGEMANAGER->addFrameImage("BS_DOWN", "image/character/enemy/boss/gethit_A.bmp", 5830, 510, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_STUN1", "image/character/enemy/boss/dizzy.bmp", 1024, 434, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BS_STUN2", "image/character/enemy/boss/roar_U.bmp", 1000, 474, 4, 2, true, RGB(255, 0, 255));
}

//젠 포인트
void stageData::createGenPoint()
{
	genStage1[0] = { 310, WINSIZEY - 80 };
	genStage1[1] = { 1200, WINSIZEY - 150};

	genStage2[0] = { 310, WINSIZEY - 80 };
	genStage2[1] = { 1600, WINSIZEY - 80 };
	genStage2[2] = { 1700, WINSIZEY - 110 };

	genStage3[0] = { 1500 , 400};
}

