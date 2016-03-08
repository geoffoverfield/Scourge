#ifndef PLAYER_H
#define PLAYER_H

#include "OperatorOverload.h"
#include "NPC.h"
using namespace std;

class Player : public OperatorOverload<Player>
{
public:
	Player();
	int Attack(int);
	int Defend(int);
	void Recruit(Player &,NPC &);
	int Train(int);
	int levelUp(int);
	void getStats();
	int getLife();
	int getXP();
	int getDefense();
	int getLevel();
	void levelUpDisplay();

	int hp, defense, xp, buff;
	int prevLevel, newLevel, level, rep, gold;
	bool attack, defend;
	string name;
private:
};

#endif