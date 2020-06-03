#ifndef _Bullet_H_
#define _Bullet_H_
#include"cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
#define SPEED 0.5f
#define Capacity 10
class Bullet :public Node {
public:
	Bullet();//�ӵ�����
	~Bullet();
	void start(Sprite* monsterSprite, Sprite* rpkBullet,Sprite* rpk);
	void autoBulletShoot(Sprite* spriteOne, Sprite* spriteTwo, Sprite* spriteThree);//�ȹ涨һ���ӵ� ��ͬ�Ե����Ǹı��˺�ֵ��ͼƬ
	void aimBulletShoot(Sprite* spriteOne, Sprite* spriteTwo, Sprite* spriteThree);
	void setUsed(Sprite* spriteOne, Sprite* spriteTwo);
	void setBulletPos(Sprite* spriteOne, Sprite* spriteTwo);
	void setWeaponPos(Sprite* spriteOne);
	//static Bullet* create(const std::string& filename);
private:
	float atkBulletValue;
	float bulletSpeed;
	int  areUsed;//�Ƿ�ʹ��
	bool  isAimed;//�Ƿ�����
	int bulletCapacity;
};
#endif // !_TollgateScene_H_
#pragma once#pragma once
