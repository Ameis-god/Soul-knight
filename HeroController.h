#pragma once
#include "cocos2d.h"
#include "Knight.h"
#include "TMX_Map.h"
#include "Animates.h"
#include "SimpleAudioEngine.h"
#include "sabre.h"
#include "MonsterManager.h"
#include "FightMap2.h"
#include "HelloWorldScene.h"
#include "Bullet.h"
#include "SafeMap.h"
#include<time.h>
USING_NS_CC;

class HeroController :public Node
{
public:
	//���ڴ����������ĺ���
	static HeroController* createHeroController();

	//��ʼ���������ĺ���
	void heroControllerInit();

	CREATE_FUNC(HeroController);



	//��ȡ˽�б���keys�ĺ���
	std::map<cocos2d::EventKeyboard::KeyCode, bool> getKeys();

	//��ȡ˽�б���direction�ĺ���
	int getDirection();

	//�ı�˽�б���direction�ĺ���
	void setDirection(int direction);



	//���°���˲��ͷſ�����˲����õĺ������Ժ�����������������
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//����Ӣ���ܶ������ĺ������ڰ���WASD����˲�����
	void startRunningAnimation(cocos2d::EventKeyboard::KeyCode keyCode);

	//ֹͣӢ���ܶ������ĺ��������ͷ�WASD����˲�����
	void stopRunningAnimation(cocos2d::EventKeyboard::KeyCode keyCode);

	void startAttackAnimation();
	void stopAttackAnimation();

	void switchWeapon(EventKeyboard::KeyCode keyCode);

	//update����,���Դ���scheduleUpdate�������ã�ÿһ֡����һ��
	void update(float dt);

	//�ж�ĳ�����Ƿ����ڱ����µĺ���
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);

	//WASD�������¹����л���õĺ�����ʵ��Ӣ�۵��ƶ����������غ����ֱ��Ӧ����һ����(���������ƶ�)�Ͱ���������(б45���ƶ�)
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode, float speed);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode1, cocos2d::EventKeyboard::KeyCode keyCode2, float speed);

	//�����¼�������
	EventListenerKeyboard* listener;



private:
	//�������水����¼�����ĸ������Ƿ����ڱ����£�
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	//�����ж�Ӣ�۵�ͼ��ǰ�����ǳ��ң�1�����ң�2������(��ʼʱĬ�ϳ���)
	int direction = 1;

};