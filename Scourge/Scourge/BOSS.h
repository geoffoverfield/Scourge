#ifndef BOSS_H
#define BOSS_H

#include "OperatorOverload.h"
class BOSS : public OperatorOverload<BOSS>
{
public:
	int level = 1;
	int HP, DP, AP;
	bool attack, defend;

	BOSS();
	int Attack(int);
	int Defend(int);
	int Bonus();
	int getLife();
private:
};

#endif