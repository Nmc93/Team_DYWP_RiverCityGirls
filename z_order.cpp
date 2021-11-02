#include "pch.h"
#include "z_order.h"

HRESULT z_order::init()
{

    return S_OK;
}

void z_order::release()
{
}

void z_order::update()
{
}

// 그리기
void z_order::render()
{
    mergeSort(0, vObj.size() - 1);

    for (int i = 0; i < vObj.size(); i++)
    {
        if (vObj[i]->key == PL)
        {
            vObj[i]->sImg->render(getMemDC(), vObj[i]->sRc.left, vObj[i]->sRc.top);
            vObj[i]->img->aniRender(getMemDC(), vObj[i]->bRc.left, vObj[i]->bRc.top, vObj[i]->ani);
        }
        else if (vObj[i]->key == EM)
        {
            vObj[i]->sImg->render(getMemDC(), vObj[i]->sRc.left, vObj[i]->sRc.top);
            vObj[i]->img->frameRender(getMemDC(), vObj[i]->bRc.left, vObj[i]->bRc.top, vObj[i]->frameNum.x, vObj[i]->frameNum.y);
        }
    }
    /*
    char test[128];
    sprintf_s(test, "%d : %d", vObj[0]->sRc.top, vObj[1]->sRc.top);
    TextOut(getMemDC(), 200, 0, test, strlen(test));
    */
    vClear();
}

void z_order::pushObject(player* pl)
{
    obj = new object;
    obj->key = PL;
    obj->sImg = pl->getSImg();
    obj->img = pl->getImage();
    obj->sRc = pl->getSRc();
    obj->bRc = pl->getRect();
    obj->ani = pl->getState()->getAni();
    obj->sY = pl->getSY();

    vObj.push_back(obj);
}

//에너미를 오브젝트에 넣기
void z_order::pushObject(vector<enemy*> vem)
{
    for (int i = 0; i < vem.size(); i++)
    {
        obj = new object;
        obj->key = EM;
        obj->sImg = vem[i]->getSImage();
        obj->img = vem[i]->getImage();
        obj->frameNum = vem[i]->getFrame();
        obj->sRc = vem[i]->getSRc();
        obj->bRc = vem[i]->getBRc();
        obj->sY = vem[i]->getSY();

        vObj.push_back(obj);
    }
}

void z_order::pushObject(itemManager* im)
{

}

//정렬===============================================================================
void z_order::merge(int left, int right)
{
    //정리한 배열을 담을 벡터를 선언 및 초기화
    vector<object*> test;
    test.clear();

    //중간지점 선언 및 초기화
    int middle = (left + right) / 2;

    //첫번째 검사 배열(left(시작지점)에서 시작)
    int first = left;
    //두번째 검사 배열(중간 + 1 에서 시작)
    int second = middle + 1;
    //배열이 정리된 후 삽입할 변수
    int startNum = left;

    //첫 배열과 두번째 배열이 끝에 닿지 않았을때
    while (first <= middle && second <= right)
    {
        //첫 배열이 두번째 배열보다 작다면
        if (vObj[first]->sY < vObj[second]->sY) test.push_back(vObj[first++]);
        else if (vObj[first]->sY >= vObj[second]->sY) test.push_back(vObj[second++]);
    }

    //첫 배열이 끝에 닿은채 끝났을 때
    if (first > middle)
    {
        //두번째 배열이 끝이 될때까지
        for (int i = second; i <= right; i++)
        {
            test.push_back(vObj[second++]);
        }
    }
    //두번째 배열이 끝에 닿은채 끝났을 때
    else if (second > right)
    {
        //첫번째 배열이 끝이 될때까지
        for (int i = first; i <= middle; i++)
        {
            test.push_back(vObj[first++]);
        }
    }

    //정리가 끝난 후 정리된 배열을 원본에 삽입
    for (int i = 0; i < test.size(); i++)
    {
        vObj[startNum++] = test[i];
    }
}

//합병 정렬
void z_order::mergeSort(int left, int right)
{
    if (left < right)
    {
        //중앙
        int mid = (left + right) / 2;

        //테스트텍스트
        //cout << left << "," << right << endl;

        //비교대상 분할
        //시작 중간
        mergeSort(left, mid);
        //중간 + 1 끝
        mergeSort(mid + 1, right);
        //합병 정렬
        merge(left, right);
    }
}
