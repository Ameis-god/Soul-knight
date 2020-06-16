#pragma once
#include "cocos2d.h"
#include "example.h"
#include "TMX_Map.h"
#include "Animates.h"
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