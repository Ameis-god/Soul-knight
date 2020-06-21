#pragma once
//
//  TMX_Map.hpp
//  MyCppGame-desktop
//
//  Created by ����Ң on 2020/6/9.
//


#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

class mapOperator : public Node {
public:
    void create(TMXTiledMap* Map);//��ͼ��ʼ��
    TMXTiledMap* returnMap();//��ȡ��ͼ,����map
    ValueMap getObjPlayer();//��objectGroup��ȡplayer
    void addSprite(Sprite* sprite);//��sprite��Ϊ�ڵ���ӽ�map
    void addController(Node* controller);
    static void moveMap(MoveBy* move,TMXTiledMap* map);//��ͼ�ƶ�,ʵ���ӽǱ仯
    void tiledJudgeInit();//���߻�ȡ���Գ�ʼ��
    bool getTiledJudge(int i);//����ʰȡ�ж�
    static bool getAndResetTiledJudgeForCreate(int i);//���߻�ȡ������д
    static bool getAndResetTiledJudgeForPick(int i);
    static bool crashJudge(int x, int y,TMXTiledMap* map);//��ͼ��ײ���
    static bool boxJudge(int x, int y,TMXTiledMap* map);//������
    static bool doorJudge(int x, int y, TMXTiledMap* map);
    static int pickObject(int x, int y,TMXTiledMap* map);
    static void show(int x, int y, TMXTiledMap* map);
    static bool transmissionDoorJudge(int x, int y, TMXTiledMap* map);
    static bool transmissionDoor1Judge(int x, int y,TMXTiledMap* map);//�����ż��,��������л�
    static bool transmissionDoor2Judge(int x, int y, TMXTiledMap* map);
    static void blueMedicineCreate(int x, int y, TMXTiledMap* map);//�ڵ�ͼ�ϴ�����ҩ
    static void blueMedicineRelease();
    static void redMedicineCreate(int x, int y,TMXTiledMap* map);//�ڵ�ͼ�ϴ�����ҩ
    static void redMedicineRelease();
    static void moneyCreate(int x, int y, TMXTiledMap* map);//�ڵ�ͼ�ϴ������
    static void moneyRelease();
    static void weaponCreate(int x, int y);//�ڵ�ͼ�ϴ�������
    static void weaponRelease();
private:
    TMXTiledMap* map;
    static Sprite* redMedicine;
    static Sprite* blueMedicine;
    static Sprite* money;
    static Sprite* weapon;
    static bool tiledJudgeForCreate[5];//���ߴ�������
    static bool tiledJudgeForPick[5];//����ʰȡ����
    /*
     ����ʰȡ���ߵ�ԭ���ǻ�ȡ��ͼ���"identity"�������ж�������ʲô����ĵ���
     �����ڳ������й��������޷��޸�ͼ�����Ե�
     Ҳ����˵���Ǳ�����취��һ��ͼ����ĵ���ֻ�ܱ���ȡһ��
     ������������һ��bool���������ж϶�Ӧ�����Ƿ��ѱ���ȡ
     һ��ʼ����true,�����Ӧ���߱���ȡ�ͱ�Ϊfalse
    */
};

