#ifndef __HERO_H__
#define __HERO_H__

#include<time.h>
#include "cocos2d.h"
#include "MovingActor.h"
//#include "SafeMap.h"

class Hero :public MovingActor
{
protected:
	int armor;//��ǰ����
	int limitArmor;//��������
	int MP;//��ǰ����
	int limitMP;//��������
	int gold;//���
	float skillCooldownTime;//������ȴʱ��
	float skillLastTime;//���ܳ���ʱ��

	bool underAttacked;//true��ʾ����ܵ�����
	bool underSkill;//true��ʾ���ڼ��ܿ���״̬
	clock_t lastAttackedTime;//���һ���յ�������ʱ��
	clock_t lastOpenSkill;//���һ�ο������ܵ�ʱ��
	clock_t currentTime;//��ǰʱ��

	int weaponNum;
	void updateHPBar();//����Ѫ��
	void updateArmorBar();//���»�����
	void updateMPBar();//��������
	void updateGold();//���½�ҵ���ʾ
	void updateSkillIcon(float dt);//���¼���ͼ��


public:

	virtual void attacked(const int value);
	virtual void updateStatus(float dt);//����״̬
	virtual void die();

	void setBars(Scene* s, const Point p);//����������
	void setGold(Scene* s, const Point p);//������ʾ���
	void setSkillIcon(Scene* s, const Point p);//���ü���ͼ��

	void changeHP(const int value);//�޸�Ѫ��
	void changeLimitHP(const int value);//�޸�Ѫ������
	void changeArmor(const int value);//�޸Ļ���ֵ
	void changeLimitArmor(const int value);//�޸Ļ�������
	void changeMP(const int value);//�޸�����
	void changeLimitMP(const int value);//�޸���������
	void changeGold(const int value);//�޸Ľ����ֵ
	void setWeaponNum(int weaponnum);
	int getWeaponNum();
	int getMP();

	bool openSkill();//��������
	void closeSkill(float dt);//�رռ���
};


#endif // !__HERO_H__




