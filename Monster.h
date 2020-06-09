#ifndef _Monster_H_
#define _Monster_H_
#include"cocos2d.h"
using namespace cocos2d;
class Monster :public Node {
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();
	void show();
	void hide();
	void reset();
	bool isAlived();
	void bindSprite(Sprite* sprite);
private:
	bool isAlive;
	Sprite* monster;
};

#endif // !_Monster_H_
#pragma once
