#include"Monster.h"
#include"MonsterManager.h"

bool MonsterManager::init() {
	createMonsters();
	this->scheduleUpdate();
	return true;
}
void MonsterManager::createMonsters() {
	Monster* monster = NULL;
	Sprite* sprite = NULL;
	for (int i = 0; i < MAX_MONITORS; i++) {
		monster = Monster::create();
		monster->bindSprite(Sprite::create("monster.png"));
		monster->reset();

		this->addChild(monster);
		monsterArr.pushBack(monster);
	}

}
void MonsterManager::update(float dt) {
	for (auto monster : monsterArr) {
		if (monster->isAlived()) {
			monster->setPositionX(monster->getPositionX() - 4);
			if (monster->getPositionX() < 0) {
				monster->hide();
			}
		}
		else {
			monster->show();
		}
	}
}