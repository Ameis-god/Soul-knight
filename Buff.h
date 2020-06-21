#ifndef __BUFF_H__
#define __BUFF_H__

#include<iostream>

enum class BuffType
{
	Poisoning,//�ж�
	Freezing,//����
	Burning,//����
	SpeedUp,//����
	SpeedDown,//����
};

class Buff
{
public:
	BuffType buffType;//buff����
	float durations;//����ʱ��

	Buff(BuffType buff, int time);
	//~Buff();
	bool operator ==(const Buff &b);
};

extern Buff poisoning;
extern Buff freezing;
extern Buff burning;
extern Buff speedUp;
extern Buff speedDown;



#endif // !__BUFF_H__

