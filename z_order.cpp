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

// �׸���
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

//���ʹ̸� ������Ʈ�� �ֱ�
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

//����===============================================================================
void z_order::merge(int left, int right)
{
    //������ �迭�� ���� ���͸� ���� �� �ʱ�ȭ
    vector<object*> test;
    test.clear();

    //�߰����� ���� �� �ʱ�ȭ
    int middle = (left + right) / 2;

    //ù��° �˻� �迭(left(��������)���� ����)
    int first = left;
    //�ι�° �˻� �迭(�߰� + 1 ���� ����)
    int second = middle + 1;
    //�迭�� ������ �� ������ ����
    int startNum = left;

    //ù �迭�� �ι�° �迭�� ���� ���� �ʾ�����
    while (first <= middle && second <= right)
    {
        //ù �迭�� �ι�° �迭���� �۴ٸ�
        if (vObj[first]->sY < vObj[second]->sY) test.push_back(vObj[first++]);
        else if (vObj[first]->sY >= vObj[second]->sY) test.push_back(vObj[second++]);
    }

    //ù �迭�� ���� ����ä ������ ��
    if (first > middle)
    {
        //�ι�° �迭�� ���� �ɶ�����
        for (int i = second; i <= right; i++)
        {
            test.push_back(vObj[second++]);
        }
    }
    //�ι�° �迭�� ���� ����ä ������ ��
    else if (second > right)
    {
        //ù��° �迭�� ���� �ɶ�����
        for (int i = first; i <= middle; i++)
        {
            test.push_back(vObj[first++]);
        }
    }

    //������ ���� �� ������ �迭�� ������ ����
    for (int i = 0; i < test.size(); i++)
    {
        vObj[startNum++] = test[i];
    }
}

//�պ� ����
void z_order::mergeSort(int left, int right)
{
    if (left < right)
    {
        //�߾�
        int mid = (left + right) / 2;

        //�׽�Ʈ�ؽ�Ʈ
        //cout << left << "," << right << endl;

        //�񱳴�� ����
        //���� �߰�
        mergeSort(left, mid);
        //�߰� + 1 ��
        mergeSort(mid + 1, right);
        //�պ� ����
        merge(left, right);
    }
}
