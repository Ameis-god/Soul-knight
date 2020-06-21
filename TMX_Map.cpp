#include "TMX_Map.h"

Sprite* mapOperator::redMedicine = new Sprite;
Sprite* mapOperator::blueMedicine = new Sprite;
Sprite* mapOperator::money = new Sprite;
bool mapOperator::tiledJudgeForCreate[5] = { false };
bool mapOperator::tiledJudgeForPick[5] = { false };

void mapOperator::create(TMXTiledMap* Map) {
    mapOperator::map = Map;//���ص�ͼ
    mapOperator::map->setAnchorPoint(Vec2(0, 0));
    mapOperator::map->setPosition(0, 0);//����ͼ���½�����ʾ�������½Ƕ���
    mapOperator::tiledJudgeInit();//���߻�ȡ���Գ�ʼ��
}

TMXTiledMap* mapOperator::returnMap() {
    return map;//��ȡ��ͼ
}

bool mapOperator::crashJudge(int x, int y,TMXTiledMap* map) {
    auto judgeLayer = map->getLayer("judgeLayer");
    /*
     ��ȡjudgeLayer��
     �������е����Զ�ͨ��judgeLayer���ȡ
     */
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    //���ݴ�������(x,y)��ȡĿ��ͼ��gidֵ
    auto property = map->getPropertiesForGID(gid).asValueMap();
    //����gidֵ��ȡ������
    return property["move"].asBool();//����һ��boolֵ,true��ִ���ƶ�,false��ִ���ƶ�
}

bool mapOperator::boxJudge(int x, int y,TMXTiledMap* map) {
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    //������һ�����ǻ�ȡ����
    if (property["identity"].asString() == "box") {
        auto sprite = judgeLayer->getTileAt(Vec2(x, y));//����ͼ���ȡΪһ������
        auto openBox = Sprite::create("openBox.png");//���û�ȡ���ľ���������ʼ����һ������,��������Ϊ�򿪵ı��������,�Ӷ�ʵ�ֿ�����
        openBox->setPosition(sprite->getPosition().x + 16, sprite->getPosition().y + 14);//+8,+7��Ϊ�˶���,�ô򿪵ı���պø���ԭ����,�ڲ�ͬ��pc���п����в��
        map->addChild(openBox, 0);
        /*
         �򿪵ı�����ӽ�map��,����Ҫ����һ�µڶ�������
         �ڶ�������0����"����"˳��,����Ϊ0��Ϊ��������ʾ�ڵذ�֮��,����֮��,�������ڵ�����
         ����Ϊʲô����Ϊ0����ϵ��
         */
        if (property["content"].asString() == "redMedicine" && mapOperator::getAndResetTiledJudgeForCreate(0)) {
            /*/
             �����ͼ���"medicineType"����Ϊ"redMedicine"������tiledJudge���ӦֵΪtrue(Ϊ�˱���һ�����߱���λ�ȡ),�ʹ�����ҩ
             */
            mapOperator::redMedicineCreate(sprite->getPosition().x + 18, sprite->getPosition().y + 16,map);//�����漰�������,Ϊ�˸��õ���ʾ
            log("red medicine got");            //�����־����һ�º�ҩ�ѱ�ʶ��,���������ֻ��ʶ��һ��
            //redMedicine->setVisible(false);//��ҩ����Ϊ���ɼ�

        }
        if (property["content"].asString() == "blueMedicine" && mapOperator::getAndResetTiledJudgeForCreate(1)) {
            /*/
             �����ͼ���"medicineType"����Ϊ"redMedicine"������tiledJudge���ӦֵΪtrue(Ϊ�˱���һ�����߱���λ�ȡ),�ʹ�����ҩ
             */
            mapOperator::blueMedicineCreate(sprite->getPosition().x + 18, sprite->getPosition().y + 16, map);//�����漰�������,Ϊ�˸��õ���ʾ
            log("red medicine got");            //�����־����һ�º�ҩ�ѱ�ʶ��,���������ֻ��ʶ��һ��
            //redMedicine->setVisible(false);//��ҩ����Ϊ���ɼ�

        }
        if (property["content"].asString() == "money" && mapOperator::getAndResetTiledJudgeForCreate(2)) {
            /*/
             �����ͼ���"medicineType"����Ϊ"redMedicine"������tiledJudge���ӦֵΪtrue(Ϊ�˱���һ�����߱���λ�ȡ),�ʹ�����ҩ
             */
            mapOperator::moneyCreate(sprite->getPosition().x + 18, sprite->getPosition().y + 16, map);//�����漰�������,Ϊ�˸��õ���ʾ
            log("red medicine got");            //�����־����һ�º�ҩ�ѱ�ʶ��,���������ֻ��ʶ��һ��
            //redMedicine->setVisible(false);//��ҩ����Ϊ���ɼ�

        }
        return true;
    }
    else return false;
}

bool mapOperator::doorJudge(int x, int y, TMXTiledMap* map) {
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    log("%s", property["move"].asString().c_str());//����һ�»�ȡ������
    if (property["identity"].asString() == "door") {
        return true;
    }
    else return false;
    //return property["move"].asBool();//����һ��boolֵ,true��ִ���ƶ�,false��ִ���ƶ�
}

int mapOperator::pickObject(int x, int y,TMXTiledMap* map) {

    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    log("%s", property["content"].asString().c_str());
    if (property["content"].asString() == "redMedicine" && getAndResetTiledJudgeForPick(0) && !getAndResetTiledJudgeForCreate(0)) {
        log("red medicine got");
        mapOperator::redMedicineRelease();
        auto effect = SimpleAudioEngine::getInstance();
        effect->playEffect("Pick.mp3");
        return 0;
    }
    else if (property["content"].asString() == "blueMedicine" && getAndResetTiledJudgeForPick(1) && !getAndResetTiledJudgeForCreate(1)) {
        log("blue medicine got");
        mapOperator::blueMedicineRelease();
        auto effect = SimpleAudioEngine::getInstance();
        effect->playEffect("Pick.mp3");
        return 1;
    }
    else if (property["content"].asString() == "money" && getAndResetTiledJudgeForPick(2) && !getAndResetTiledJudgeForCreate(2)) {
        log("money got");
        mapOperator::moneyRelease();
        auto effect = SimpleAudioEngine::getInstance();
        effect->playEffect("Pick.mp3");
        return 2;
    }
    else if (property["content"].asString() == "weapon" && getAndResetTiledJudgeForPick(3) && getAndResetTiledJudgeForCreate(3)) {
        log("weapon got");
        mapOperator::blueMedicineRelease();
        auto effect = SimpleAudioEngine::getInstance();
        effect->playEffect("Pick.mp3");
        return 3;
    }
    else return 4;
}

void mapOperator::show(int x, int y,TMXTiledMap* map) {
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    log("%s", property["move"].asString().c_str());//����һ�»�ȡ������
    if (property["identity"].asString() == "show") {//�жϵ�ǰͼ���Ƿ�Ϊչʾ��
        auto title = property["name"].asString();//��ȡ����
        auto message = property["character"].asString();//��ȡ��������
        MessageBox(title.c_str(), message.c_str());//ͨ��messageBox���
    }
}

void mapOperator::redMedicineCreate(int x, int y,TMXTiledMap* map) {
    redMedicine = Sprite::create("redMedicine.png");
    redMedicine->setPosition(x, y);
    map->addChild(redMedicine, 1);
}

void mapOperator::blueMedicineCreate(int x, int y, TMXTiledMap* map) {
   blueMedicine = Sprite::create("blueMedicine.png");
    blueMedicine->setPosition(x, y);
    map->addChild(blueMedicine, 1);
}
void mapOperator::moneyCreate(int x, int y, TMXTiledMap* map) {
    redMedicine = Sprite::create("money.png");
    redMedicine->setPosition(x, y);
    map->addChild(money, 1);
}

void mapOperator::redMedicineRelease() {
    redMedicine->setVisible(false);
}

void mapOperator::blueMedicineRelease() {
    blueMedicine->setVisible(false);
}
void mapOperator::moneyRelease() {
    money->setVisible(false);
}

bool mapOperator::transmissionDoorJudge(int x, int y, TMXTiledMap* map) {//������ʶ��,������һ�ŵ�ͼ����һ�ŵ�ͼ,ԭ��һ��,��û����ʵ��
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    if (property["identity"].asString() == "transmissionDoor") {
        return true;
    }
    else return false;
}

bool mapOperator::transmissionDoor1Judge(int x, int y,TMXTiledMap* map) {//������ʶ��,������һ�ŵ�ͼ����һ�ŵ�ͼ,ԭ��һ��,��û����ʵ��
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    if (property["identity"].asString() == "transmissionDoor2") {
        return true;
    }
    else return false;
}

bool mapOperator::transmissionDoor2Judge(int x, int y, TMXTiledMap* map) {//������ʶ��,������һ�ŵ�ͼ����һ�ŵ�ͼ,ԭ��һ��,��û����ʵ��
    auto judgeLayer = map->getLayer("judgeLayer");
    auto gid = judgeLayer->getTileGIDAt(Vec2(x, y));
    auto property = map->getPropertiesForGID(gid).asValueMap();
    if (property["identity"].asString() == "transmissionDoor3") {
        return true;
    }
    else return false;
}

ValueMap mapOperator::getObjPlayer() {
    auto objectGroup = map->getObjectGroup("objectLayer");//��ȡ�����
    return objectGroup->getObject("player");//�Ӷ�����ȡplayer
}

void mapOperator::addSprite(Sprite* sprite) {
    map->addChild(sprite, 2);//��������ӵ���ͼ,�������Ⱦ˳����1,��ζ�������ڸ���Ⱦ˳����0�Ķ���,����ǰ����ܹ�
}

void mapOperator::moveMap(MoveBy* move,TMXTiledMap* map) {
    map->runAction(move);//��ͼ�ƶ�
}

void mapOperator::tiledJudgeInit() {
    for (int i = 0; i < 5; i++) {
        tiledJudgeForPick[i] = true;//��ͼ��ȡ���Գ�ʼ��
        tiledJudgeForCreate[i] = true;
    }
}
bool mapOperator::getAndResetTiledJudgeForCreate(int i) {
    if (tiledJudgeForCreate[i] == true) {//�����ӦֵΪtrue����������߻�û�б���ȡ��
        tiledJudgeForCreate[i] = false;//�������޸�Ϊfalse,���������Ѿ���ȡ�����������
        return true;
    }
    else return false;
}

bool mapOperator::getAndResetTiledJudgeForPick(int i) {
    if (tiledJudgeForPick[i] == true) {//�����ӦֵΪtrue����������߻�û�б���ȡ��
        tiledJudgeForPick[i] = false;//�������޸�Ϊfalse,���������Ѿ���ȡ�����������
        return true;
    }
    else return false;
}

void mapOperator::addController(Node* controller) {
    map->addChild(controller, 2);
}