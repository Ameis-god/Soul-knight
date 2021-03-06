#ifndef __HERO_H__
#define __HERO_H__

#include<time.h>
#include "cocos2d.h"
#include "MovingActor.h"
//#include "SafeMap.h"

class Hero :public MovingActor
{
protected:
	int armor;//当前护甲
	int limitArmor;//护甲上限
	int MP;//当前蓝量
	int limitMP;//蓝量上限
	int gold;//金币
	float skillCooldownTime;//技能冷却时间
	float skillLastTime;//技能持续时间

	bool underAttacked;//true表示最近受到攻击
	bool underSkill;//true表示处于技能开启状态
	clock_t lastAttackedTime;//最后一次收到攻击的时间
	clock_t lastOpenSkill;//最后一次开启技能的时间
	clock_t currentTime;//当前时间

	int weaponNum;
	void updateHPBar();//更新血条
	void updateArmorBar();//更新护甲条
	void updateMPBar();//更新蓝条
	void updateGold();//更新金币的显示
	void updateSkillIcon(float dt);//更新技能图标


public:

	virtual void attacked(const int value);
	virtual void updateStatus(float dt);//更新状态
	virtual void die();

	void setBars(Scene* s, const Point p);//设置属性条
	void setGold(Scene* s, const Point p);//设置显示金币
	void setSkillIcon(Scene* s, const Point p);//设置技能图标

	void changeHP(const int value);//修改血量
	void changeLimitHP(const int value);//修改血量上限
	void changeArmor(const int value);//修改护甲值
	void changeLimitArmor(const int value);//修改护甲上限
	void changeMP(const int value);//修改蓝量
	void changeLimitMP(const int value);//修改蓝量上限
	void changeGold(const int value);//修改金币数值
	void setWeaponNum(int weaponnum);
	int getWeaponNum();
	int getMP();

	bool openSkill();//开启技能
	void closeSkill(float dt);//关闭技能
};


#endif // !__HERO_H__




