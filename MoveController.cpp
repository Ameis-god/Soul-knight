#include "MoveController.h"

//���ڴ����������ĺ���
MoveController* MoveController::createMoveController() {
    MoveController* moveController=MoveController::create() ;
    moveController->controllerInit();
    return moveController;
}

//��ʼ���������ĺ���
void MoveController::controllerInit() {
    listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MoveController::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MoveController::onKeyReleased, this);
}


//��ȡ˽�б���keys�ĺ���
std::map<cocos2d::EventKeyboard::KeyCode, bool> MoveController::getKeys() {
    return keys;
}

//��ȡ˽�б���direction�ĺ���
int MoveController::getDirection() {
    return direction;
}

//�ı�˽�б���direction�ĺ���
void MoveController::setDirection(int Direction) {
    direction = Direction;
}


//���°���˲��ͷſ�����˲����õĺ������Ժ�����������������
void MoveController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    startRunningAnimation(keyCode);
    keys[keyCode] = true;
}

void MoveController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    stopRunningAnimation(keyCode);
    keys[keyCode] = false;
}

//update����,���Դ���scheduleUpdate�������ã�ÿһ֡����һ��
void MoveController::update(float dt) {
    const auto A = EventKeyboard::KeyCode::KEY_A;
    const auto D = EventKeyboard::KeyCode::KEY_D;
    const auto W = EventKeyboard::KeyCode::KEY_W;
    const auto S = EventKeyboard::KeyCode::KEY_S;

    //�����ٶ���ʱ�̶������ڿ��Ը�Ϊ�ɲ���dt������
    const float speed = 2;

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
bool MoveController::isKeyPressed(EventKeyboard::KeyCode keyCode) {
    if (getKeys()[keyCode]) {
        return true;
    }
    else {
        return false;
    }
}

//WASD�������¹����л���õĺ�����ʵ��Ӣ�۵��ƶ����������غ����ֱ��Ӧ����һ����(���������ƶ�)�Ͱ���������(б45���ƶ�)
void MoveController::keyPressedDuration(EventKeyboard::KeyCode keyCode, float speed) {

    //�ƶ���������
    float offsetX = 0, offsetY = 0;

    //����ʵ����ÿ֡�ж�ǽ�ڣ����ڿ��Խ����޸ģ��Ӷ�����ͼ���
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
        offsetX = -speed;
        if (getChildByTag(1)->getPositionX() - getChildByTag(1)->getContentSize().width / 2 + offsetY <= 0)
            offsetX = 0;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        offsetX = speed;
        if (getChildByTag(1)->getPositionX() + getChildByTag(1)->getContentSize().width / 2 + offsetY >= 1024)
            offsetX = 0;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        offsetY = speed;
        if (getChildByTag(1)->getPositionY() + getChildByTag(1)->getContentSize().height / 2 + offsetY >= 768)
            offsetY = 0;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        offsetY = -speed;
        if (getChildByTag(1)->getPositionY() - getChildByTag(1)->getContentSize().height / 2 + offsetY <= 0)
            offsetY = 0;
        break;
    }

    auto moveBy = MoveBy::create(0.00005, Vec2(offsetX, offsetY));
    getChildByTag(1)->runAction(moveBy);
}

void MoveController::keyPressedDuration(EventKeyboard::KeyCode keyCode1, EventKeyboard::KeyCode keyCode2, float speed) {
    float offsetX = 0, offsetY = 0;
    switch (keyCode1) {
        //����ʵ����ÿ֡�ж�ǽ�ڣ����ڿ��Խ����޸ģ��Ӷ�����ͼ���
    case EventKeyboard::KeyCode::KEY_A:
        offsetX = -speed / sqrt(2);
        if (getChildByTag(1)->getPositionX() - getChildByTag(1)->getContentSize().width / 2 + offsetY <= 0)
            offsetX = 0;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        offsetX = speed / sqrt(2);
        if (getChildByTag(1)->getPositionX() + getChildByTag(1)->getContentSize().width / 2 + offsetY >= 1024)
            offsetX = 0;
        break;
    }
    switch (keyCode2) {
    case EventKeyboard::KeyCode::KEY_W:
        offsetY = speed / sqrt(2);
        if (getChildByTag(1)->getPositionY() + getChildByTag(1)->getContentSize().height / 2 + offsetY >= 768)
            offsetY = 0;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        offsetY = -speed / sqrt(2);
        if (getChildByTag(1)->getPositionY() - getChildByTag(1)->getContentSize().height / 2 + offsetY <= 0)
            offsetY = 0;
        break;
    }
    auto moveBy = MoveBy::create(0.00005, Vec2(offsetX, offsetY));
    getChildByTag(1)->runAction(moveBy);
}

//����Ӣ���ܶ������ĺ������ڰ���WASD����˲�����
void MoveController::startRunningAnimation(EventKeyboard::KeyCode keyCode) {
    Vector<SpriteFrame*> frameVec1;
    auto frame1 = SpriteFrame::create("Knight_right_standing.png", Rect(0, 0, 100, 100));
    frameVec1.pushBack(frame1);
    auto frame2 = SpriteFrame::create("Knight_right_running.png", Rect(0, 0, 100, 100));
    frameVec1.pushBack(frame2);
    auto animation1 = Animation::createWithSpriteFrames(frameVec1);
    animation1->setLoops(-1);
    animation1->setDelayPerUnit(0.1f);
    auto animate1 = Animate::create(animation1);

    Vector<SpriteFrame*> frameVec2;
    auto frame3 = SpriteFrame::create("Knight_left_standing.png", Rect(0, 0, 100, 100));
    frameVec2.pushBack(frame3);
    auto frame4 = SpriteFrame::create("Knight_left_running.png", Rect(0, 0, 100, 100));
    frameVec2.pushBack(frame4);
    auto animation2 = Animation::createWithSpriteFrames(frameVec2);
    animation2->setLoops(-1);
    animation2->setDelayPerUnit(0.1f);
    auto animate2 = Animate::create(animation2);

    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        getChildByTag(1)->runAction(animate2);
        animate2->setTag(1);
        setDirection(2);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        getChildByTag(1)->runAction(animate1);
        animate1->setTag(1);
        setDirection(1);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
        if (getDirection() == 1) {
            getChildByTag(1)->runAction(animate1);
            animate1->setTag(1);
        }
        else if (getDirection() == 2) {
            getChildByTag(1)->runAction(animate2);
            animate2->setTag(1);
        }
    }

}

//ֹͣӢ���ܶ������ĺ��������ͷ�WASD����˲�����
void MoveController::stopRunningAnimation(EventKeyboard::KeyCode keyCode) {
    Vector<SpriteFrame*> frameVec1;
    auto frame1 = SpriteFrame::create("Knight_right_standing.png", Rect(0, 0, 100, 100));
    frameVec1.pushBack(frame1);
    auto animation1 = Animation::createWithSpriteFrames(frameVec1);
    animation1->setLoops(-1);
    animation1->setDelayPerUnit(-1);
    auto animate1 = Animate::create(animation1);

    Vector<SpriteFrame*> frameVec2;
    auto frame2 = SpriteFrame::create("Knight_left_standing.png", Rect(0, 0, 100, 100));
    frameVec2.pushBack(frame2);
    auto animation2 = Animation::createWithSpriteFrames(frameVec2);
    animation2->setLoops(-1);
    animation2->setDelayPerUnit(-1);
    auto animate2 = Animate::create(animation2);

    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        getChildByTag(1)->stopActionByTag(1);
        getChildByTag(1)->runAction(animate2);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        getChildByTag(1)->stopActionByTag(1);
        getChildByTag(1)->runAction(animate1);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
        getChildByTag(1)->stopActionByTag(1);
        if (getDirection() == 1) {
            getChildByTag(1)->runAction(animate1);
        }
        else if (getDirection() == 2) {
            getChildByTag(1)->runAction(animate2);
        }
    }
}