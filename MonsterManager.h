#ifndef _MonsterManager_H_
#define _MonsterManager_H_
#include"cocos2d.h"
#include"Monster.h"
USING_NS_CC;
#define MAX_MONSTER 10
class MonsterManager :public Node {
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();
	virtual void update(float dt);
private:
	void createMonsters();
	Vector<Monster*>monsterArr;
};
#endif // !_MonsterManager_H_
#pragma once
