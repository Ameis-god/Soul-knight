#include"Monster.h"
using namespace cocos2d;

Monster::Monster() {
	isAlive = false;
}
Monster::~Monster() {

}
bool Monster::init() {
	return true;
}
void Monster::hide() {
	setVisible(false);
	reset();
	isAlive = false;
}
void Monster::show() {
	setVisible(true);
	//reset();
	isAlive = true;
}
void Monster::reset()
{
	setPosition(Point(600 + CCRANDOM_0_1() * 200, 200 - CCRANDOM_0_1() * 100));

}

bool Monster::isAlived() {
	return isAlive;
}
void Monster::bindSprite(Sprite* sprite) {
	this->monster = sprite;
	this->addChild(monster);
}