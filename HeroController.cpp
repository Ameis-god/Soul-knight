#include "HeroController.h"
using namespace CocosDenshion;

//���ڴ����������ĺ���
HeroController* HeroController::createHeroController() {
	HeroController* controller = HeroController::create();
	controller->heroControllerInit();
	controller->scheduleUpdate();
	return controller;
}

//��ʼ���������ĺ���
void HeroController::heroControllerInit() {
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HeroController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HeroController::onKeyReleased, this);
}


//��ȡ˽�б���keys�ĺ���
std::map<cocos2d::EventKeyboard::KeyCode, bool> HeroController::getKeys() {
	return keys;
}

//��ȡ˽�б���direction�ĺ���
int HeroController::getDirection() {
	return direction;
}

//�ı�˽�б���direction�ĺ���
void HeroController::setDirection(int Direction) {
	direction = Direction;
}


//���°���˲��ͷſ�����˲����õĺ���
void HeroController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D ||
		keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S)
		startRunningAnimation(keyCode);
	else if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		switchWeapon(keyCode);
		auto effect = SimpleAudioEngine::getInstance();
		effect->playEffect("changeWeapon.mp3");
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		int X = (dynamic_cast<Knight*>(getChildByTag(1))->getPosition().x) / 32;//����ת��
		int Y = 100 - (dynamic_cast<Knight*>(getChildByTag(1))->getPosition().y) / 32;
		int object=mapOperator::pickObject(X, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		switch(object){
		case 0:
			dynamic_cast<Knight*>(getChildByTag(1))->changeHP(2);
			break;
		case 1:
			dynamic_cast<Knight*>(getChildByTag(1))->changeMP(80);
			break;
		case 2:
			dynamic_cast<Knight*>(getChildByTag(1))->changeGold(1);
			break;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		startAttackAnimation();
		if (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum() == 1) {
			dynamic_cast<Sabre*>(getChildByTag(2))->isLanched(1);
			auto effect = SimpleAudioEngine::getInstance();
			effect->playEffect("SabreAttack.mp3");
		}
		else if (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum() == 3 && dynamic_cast<Knight*>(getChildByTag(1))->getMP() > 1) {
			dynamic_cast<Sabre*>(getChildByTag(2))->isLanched(2);
			auto effect = SimpleAudioEngine::getInstance();
			effect->playEffect("SabreAttack.mp3");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
		dynamic_cast<Knight*>(getChildByTag(1))->openSkill();
		dynamic_cast<Knight*>(getChildByTag(1))->changeMP(-50);
	}
	keys[keyCode] = true;
}

void HeroController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D ||
		keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S)
		stopRunningAnimation(keyCode);
	else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		stopAttackAnimation();
	keys[keyCode] = false;
}

//update����,���Դ���scheduleUpdate�������ã�ÿһ֡����һ��
void HeroController::update(float dt) {
	const auto A = EventKeyboard::KeyCode::KEY_A;
	const auto D = EventKeyboard::KeyCode::KEY_D;
	const auto W = EventKeyboard::KeyCode::KEY_W;
	const auto S = EventKeyboard::KeyCode::KEY_S;

	float speed = dynamic_cast<Knight*>(getChildByTag(1))->getMovingSpeed();

	//WASD�а���һ���������
	if (isKeyPressed(A) && !isKeyPressed(S) && !isKeyPressed(D) && !isKeyPressed(W)) {
		keyPressedDuration(A, speed);
	}
	else if (isKeyPressed(D) && !isKeyPressed(S) && !isKeyPressed(A) && !isKeyPressed(W)) {
		keyPressedDuration(D, speed);
	}
	else if (isKeyPressed(W) && !isKeyPressed(S) && !isKeyPressed(A) && !isKeyPressed(D)) {
		keyPressedDuration(W, speed);
	}
	else if (isKeyPressed(S) && !isKeyPressed(A) && !isKeyPressed(D) && !isKeyPressed(W)) {
		keyPressedDuration(S, speed);
	}

	//WA�к�SD�и�����һ���������
	else if (isKeyPressed(A) && isKeyPressed(W) && !isKeyPressed(D) && !isKeyPressed(S)) {
		keyPressedDuration(A, W, speed);
	}
	else if (isKeyPressed(A) && isKeyPressed(S) && !isKeyPressed(D) && !isKeyPressed(W)) {
		keyPressedDuration(A, S, speed);
	}
	else if (isKeyPressed(D) && isKeyPressed(W) && !isKeyPressed(A) && !isKeyPressed(S)) {
		keyPressedDuration(D, W, speed);
	}
	else if (isKeyPressed(D) && isKeyPressed(S) && !isKeyPressed(A) && !isKeyPressed(W)) {
		keyPressedDuration(D, S, speed);
	}

	//��ֹ����������ͬʱ����ʱ����Ч���쳣
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		stopRunningAnimation(EventKeyboard::KeyCode::KEY_D);
	}

}

//�ж�ĳ�����Ƿ����ڱ����µĺ���
bool HeroController::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (getKeys()[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

//WASD�������¹����л���õĺ�����ʵ��Ӣ�۵��ƶ����������غ����ֱ��Ӧ����һ����(���������ƶ�)�Ͱ���������(б45���ƶ�)
void HeroController::keyPressedDuration(EventKeyboard::KeyCode keyCode, float speed) {
	int X = 0;
	int Y = 0;
	bool fightBegin = false;
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		X = (getChildByTag(1)->getPosition().x + 7) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y) / 32;
		if (mapOperator::crashJudge(X-1,Y,dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(-speed, 0));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(speed, 0));
			getChildByTag(1)->runAction(moveBy);
			getParent()->runAction(moveBy1);
			if (mapOperator::transmissionDoorJudge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
			    Director::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene()));
			}
			else if (mapOperator::transmissionDoor1Judge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, FightMap2::createScene()));
			}
			else if (mapOperator::transmissionDoor2Judge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, SafeMap::createScene()));
			}
		}
		mapOperator::show(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		mapOperator::boxJudge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		X = (getChildByTag(1)->getPosition().x -20) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y) / 32;
		if (mapOperator::crashJudge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(speed, 0));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(-speed, 0));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
			if (mapOperator::transmissionDoorJudge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene()));
			}
			else if (mapOperator::transmissionDoor1Judge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, FightMap2::createScene()));
			}
			else if (mapOperator::transmissionDoor2Judge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, SafeMap::createScene()));
			}
		}
		mapOperator::show(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		mapOperator::boxJudge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	case EventKeyboard::KeyCode::KEY_W:
		X = (getChildByTag(1)->getPosition().x) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y-10) / 32;
		if (mapOperator::crashJudge(X , Y-1 , dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(0, speed));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(0, -speed));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
			if (mapOperator::transmissionDoorJudge(X , Y-1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene()));
			}
			else if (mapOperator::transmissionDoor1Judge(X , Y-1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, FightMap2::createScene()));
			}
			else if (mapOperator::transmissionDoor2Judge(X , Y-1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, SafeMap::createScene()));
			}
		}
		mapOperator::show(X , Y-1, dynamic_cast<TMXTiledMap*>(getParent()));
		mapOperator::boxJudge(X , Y-1, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	case EventKeyboard::KeyCode::KEY_S:
		X = (getChildByTag(1)->getPosition().x) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y+10) / 32;
		if (mapOperator::crashJudge(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(0,-speed));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(0, speed));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
			if (mapOperator::transmissionDoorJudge(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene()));
			}
			else if (mapOperator::transmissionDoor1Judge(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, FightMap2::createScene()));
			}
			else if (mapOperator::transmissionDoor2Judge(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()))) {
				Director::getInstance()->replaceScene(TransitionFade::create(1.5, SafeMap::createScene()));
			}
		}
		mapOperator::show(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()));
		mapOperator::boxJudge(X , Y+1, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	}
}

void HeroController::keyPressedDuration(EventKeyboard::KeyCode keyCode1, EventKeyboard::KeyCode keyCode2, float speed) {
	int X = 0;
	int Y = 0;
	switch (keyCode1) {
	case EventKeyboard::KeyCode::KEY_A:
		X = (getChildByTag(1)->getPosition().x + 7) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y) / 32;
		if (mapOperator::crashJudge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(-speed / sqrt(2), 0));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(speed / sqrt(2), 0));
			getChildByTag(1)->runAction(moveBy);
			getParent()->runAction(moveBy1);
		}
		mapOperator::boxJudge(X - 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		X = (getChildByTag(1)->getPosition().x - 20) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y) / 32;
		if (mapOperator::crashJudge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(speed / sqrt(2), 0));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(-speed / sqrt(2), 0));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
		}
		mapOperator::boxJudge(X + 1, Y, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	}
	switch (keyCode2) {
	case EventKeyboard::KeyCode::KEY_W:
		X = (getChildByTag(1)->getPosition().x) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y - 10) / 32;
		if (mapOperator::crashJudge(X, Y - 1, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(0, speed / sqrt(2)));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(0, -speed / sqrt(2)));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
		}
		mapOperator::boxJudge(X, Y - 1, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	case EventKeyboard::KeyCode::KEY_S:
		X = (getChildByTag(1)->getPosition().x) / 32;//����ת��
		Y = 100 - (getChildByTag(1)->getPosition().y + 10) / 32;
		if (mapOperator::crashJudge(X, Y + 1, dynamic_cast<TMXTiledMap*>(getParent()))) {
			auto moveBy = MoveBy::create(0.00005, Vec2(0, -speed / sqrt(2)));
			auto moveBy1 = MoveBy::create(0.00005, Vec2(0, speed / sqrt(2)));
			getChildByTag(1)->runAction(moveBy);
			mapOperator::moveMap(moveBy1, dynamic_cast<TMXTiledMap*>(getParent()));
		}
		mapOperator::boxJudge(X, Y + 1, dynamic_cast<TMXTiledMap*>(getParent()));
		break;
	}
}


//����Ӣ���ܶ������ĺ������ڰ���WASD����˲�����
void HeroController::startRunningAnimation(EventKeyboard::KeyCode keyCode) {

	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		auto animate = new Animate;
		switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
		case 0:
			animate = Animates::leftRunningWithPistolAnimate();
			break;
		case 1:
			animate = Animates::leftRunningWithSabreAnimate();
			break;
		case 2:
			animate = Animates::leftRunningWithRpkAnimate();
			break;
		case 3:
			animate=  Animates::leftRunningWithWandAnimate();
			break;
		}
		getChildByTag(1)->runAction(animate);
		animate->setTag(1);
		setDirection(2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		auto animate = new Animate;
		switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
		case 0:
			animate = Animates::rightRunningWithPistolAnimate();
			break;
		case 1:
			animate = Animates::rightRunningWithSabreAnimate();
			break;
		case 2:
			animate = Animates::rightRunningWithRpkAnimate();
			break;
		case 3:
			animate = Animates::rightRunningWithWandAnimate();
			break;
		}
		getChildByTag(1)->runAction(animate);
		animate->setTag(1);
		setDirection(1);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (getDirection() == 1) {
			auto animate = new Animate;
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 0:
				animate = Animates::rightRunningWithPistolAnimate();
				break;
			case 1:
				animate = Animates::rightRunningWithSabreAnimate();
				break;
		    case 2:
				animate = Animates::rightRunningWithRpkAnimate();
				break;
			case 3:
				animate = Animates::rightRunningWithWandAnimate();
				break;
			}
			getChildByTag(1)->runAction(animate);
			animate->setTag(1);
		}
		else if (getDirection() == 2) {
			auto animate = new Animate;
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 0:
				animate = Animates::leftRunningWithPistolAnimate();
				break;
			case 1:
				animate = Animates::leftRunningWithSabreAnimate();
				break;
			case 2:
				animate = Animates::leftRunningWithRpkAnimate();
				break;
			case 3:
				animate = Animates::leftRunningWithWandAnimate();
				break;
			}
			getChildByTag(1)->runAction(animate);
			animate->setTag(1);
		}
	}

}

//ֹͣӢ���ܶ������ĺ��������ͷ�WASD����˲�����
void HeroController::stopRunningAnimation(EventKeyboard::KeyCode keyCode) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		getChildByTag(1)->stopActionByTag(1);
		switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
		case 0:
			getChildByTag(1)->runAction(Animates::leftStopWithPistolAnimate());
			break;
		case 1:
			getChildByTag(1)->runAction(Animates::leftStopWithSabreUpAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithRpkAnimate());
			break;
		case 3:
			getChildByTag(1)->runAction(Animates::leftStopWithWandUpAnimate());
			break;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		getChildByTag(1)->stopActionByTag(1);
		switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
		case 0:
			getChildByTag(1)->runAction(Animates::rightStopWithPistolAnimate());
			break;
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithSabreUpAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::rightStopWithRpkAnimate());
			break;
		case 3:
			getChildByTag(1)->runAction(Animates::rightStopWithWandUpAnimate());
			break;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
		getChildByTag(1)->stopActionByTag(1);
		if (getDirection() == 1) {
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 0:
				getChildByTag(1)->runAction(Animates::rightStopWithPistolAnimate());
				break;
			case 1:
				getChildByTag(1)->runAction(Animates::rightStopWithSabreUpAnimate());
				break;
			case 2:
				getChildByTag(1)->runAction(Animates::rightStopWithRpkAnimate());
				break;
			case 3:
				getChildByTag(1)->runAction(Animates::rightStopWithWandUpAnimate());
				break;
			}
		}
		else if (getDirection() == 2) {
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 0:
				getChildByTag(1)->runAction(Animates::leftStopWithPistolAnimate());
				break;
			case 1:
				getChildByTag(1)->runAction(Animates::leftStopWithSabreUpAnimate());
				break;
			case 2:
				getChildByTag(1)->runAction(Animates::leftStopWithRpkAnimate());
				break;
			case 3:
				getChildByTag(1)->runAction(Animates::rightStopWithWandUpAnimate());
				break;
			}
		}
	}
}

void HeroController::startAttackAnimation() {
	switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
	case 1:
		switch (getDirection()) {
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithSabreDownAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithSabreDownAnimate());
			break;
		}
		break;
	case 3:
		switch (getDirection()) {
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithWandDownAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithWandDownAnimate());
			break;
		}
		break;
	}
	
}

void HeroController::stopAttackAnimation() {
	switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
	case 1:
		switch (getDirection()) {
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithSabreUpAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithSabreUpAnimate());
			break;
		}
		break;
	case 3:
		switch (getDirection()) {
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithWandUpAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithWandUpAnimate());
			break;
		}
		break;
	}
}

void HeroController::switchWeapon(EventKeyboard::KeyCode keyCode) {
	dynamic_cast<Knight*>(getChildByTag(1))->setWeaponNum(dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum() + 1);
	if (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum() > 3) {
		dynamic_cast<Knight*>(getChildByTag(1))->setWeaponNum(0);
		switch (getDirection()) {
		case 1:
			getChildByTag(1)->runAction(Animates::rightStopWithPistolAnimate());
			break;
		case 2:
			getChildByTag(1)->runAction(Animates::leftStopWithPistolAnimate());
			break;
		}
	}

	else {
		switch (getDirection()) {
		case 1:
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 1:
				getChildByTag(1)->runAction(Animates::rightStopWithSabreUpAnimate());
				break;
			case 2:
				getChildByTag(1)->runAction(Animates::rightStopWithRpkAnimate());
				break;
			case 3:
				getChildByTag(1)->runAction(Animates::rightStopWithWandUpAnimate());
				break;
			}
			break;
		case 2:
			switch (dynamic_cast<Knight*>(getChildByTag(1))->getWeaponNum()) {
			case 1:
				getChildByTag(1)->runAction(Animates::leftStopWithSabreUpAnimate());
				break;
			case 2:
				getChildByTag(1)->runAction(Animates::leftStopWithRpkAnimate());
				break;
			case 3:
				getChildByTag(1)->runAction(Animates::leftStopWithWandUpAnimate());
				break;
			}
			break;
		}
	}
}


