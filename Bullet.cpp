#include"Bullet.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"MyHelloWorldScene.h"
#include"SecondScene.h"
#include "cocos2d.h"
#include "Bullet.h"
using namespace cocos2d;
#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)

Bullet::Bullet() {
	atkBulletValue = 1;
	bulletSpeed=SPEED; 
	areUsed=0;//�Ƿ�ʹ��
	isAimed=false;
}
Bullet::~Bullet() {

}
//One is enemy  Two is bullet Three is weapon
void Bullet::autoBulletShoot(Sprite* spriteOne, Sprite* spriteTwo,Sprite* spriteThree) {
	if (areUsed < Capacity) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point aimPos = spriteOne->getPosition();
		if (spriteOne->getBoundingBox().containsPoint(spriteTwo->getPosition())) {
			setBulletPos(spriteThree, spriteTwo);
		}
		//Point dstPos = spriteTwo->getPosition();
		auto moveTo = MoveTo::create(bulletSpeed, aimPos);
		ScaleTo* scaleTo = ScaleTo::create(0.0f, 0.0f, 0.0f);
		areUsed++;
		Action* action = Sequence::create(moveTo, scaleTo, NULL);
		spriteTwo->runAction(action);
	}
}
void Bullet::aimBulletShoot(Sprite* spriteOne, Sprite* spriteTwo, Sprite* spriteThree) {
	if (areUsed < Capacity) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point aimPos = spriteOne->getPosition();
		Point dstPos = spriteTwo->getPosition();
		auto moveTo = MoveTo::create(bulletSpeed, aimPos);
		ScaleTo* scaleTo = ScaleTo::create(0.0f, 0.0f, 0.0f);
		areUsed++;
		
			isAimed = true;
		
		Action* action = Sequence::create(moveTo, scaleTo, NULL);
		spriteTwo->runAction(action);
	}
}


//  ���� ��Ҫ��ʱ������������


void Bullet::setUsed(Sprite* spriteOne) {
	if (isAimed == true) {
		//isAimed = true;
		Blink* blink = Blink::create(1.0f, 1);
		spriteOne->runAction(blink);
	}
}
//One is weapon Two is bullet
void Bullet::setBulletPos(Sprite* spriteOne, Sprite* spriteTwo) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Point pos = spriteOne->getPosition();
	//Sprite* bullet = Sprite::create("rpkBullet.png");
	spriteTwo->setPosition(pos.x,pos.y);
	spriteTwo->setScale(0.8f);
	b = spriteTwo->getPosition();
	addChild(spriteTwo);
}

void Bullet::setWeaponPos(Sprite * spriteOne){	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Sprite* spriteOne = Sprite::create("rpk.png");
	spriteOne->setPosition(Point(600, 330));
	//Point pos = spriteOne->getPosition();
	spriteOne->setScale(2.5f);
	addChild(spriteOne);
	//Sprite* spriteTwo = Sprite::create("rpkBullet.png");	
}

Point Bullet::start(Sprite* monsterSprite, Sprite* rpkBullet, Sprite* rpk) {
	/*
	��������һ����ǩ
		1.����һ������
		2.����һ���ӵ�
		3.��׼���
		4.ȷ����׼
	*/
	Sprite* rpkOne = rpk;

	rpkBullet = Sprite::create("rpkBullet.png");
	rpkBullet->setScale(0.1);
	//if (areUsed < Capacity) {
		setBulletPos(rpkOne, rpkBullet);
	//}
	aimBulletShoot(monsterSprite, rpkBullet, rpkOne);
	Point pos = rpkBullet->getPosition();
	setUsed(monsterSprite);
	return pos;
}
Point Bullet::bulletPos() {
	return b;
}