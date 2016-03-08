#include "Player.h"
#include "TreasureChest.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

Player::Player()
{
	hp = 100;
	defense = 0;
	xp = 0;
	buff = 0;
	prevLevel = 0;
	newLevel = 1;
	level = 1;
	rep = 5;
	gold = 50;
	attack = defend = false;
	name = "";
}

int Player::Attack(int a)
{
	level = a;
	int attk = (hp / level) + rep;
	__asm
	{
		mov eax, attk
			mov ebx, a
			add eax, ebx
			mov attk, eax
	}
	buff = rand() % 10;
	attk = attk + buff;
	buff = 0;

	return attk;
}

int Player::Defend(int d)
{
	defense = 25;
	int lev = d;
	defense = (defense*lev) + lev;

	if (defense >= 75)
		defense = defense - lev;

	return defense;
}

void Player::Recruit(Player &player, NPC &npc)
{
	npc = NPC();
	player.rep += npc.rep;
	cout << "You successfully recruited " << npc.name << "." << endl;
	cout << "Your current Reputation Score is: " << player.rep << endl;
}

int Player::Train(int t)
{
	xp = xp + t;
	levelUp(xp);
	return xp;
}

int Player::levelUp(int l)
{
	if (l <= 50)
	{
		prevLevel = level;
		level = 1;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 50 && l <= 100)
	{
		prevLevel = level;
		level = 2;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 100 && l <= 150)
	{
		prevLevel = level;
		level = 3;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 150 && l <= 200)
	{
		prevLevel = level;
		level = 4;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 200 && l <= 275)
	{
		prevLevel = level;
		level = 5;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 275 && l <= 350)
	{
		prevLevel = level;
		level = 6;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 350 && l <= 425)
	{
		prevLevel = level;
		level = 7;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 425 && l <= 500)
	{
		prevLevel = level;
		level = 8;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 500 && l <= 600)
	{
		prevLevel = level;
		level = 9;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 600 && l <= 700)
	{
		prevLevel = level;
		level = 10;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 700 && l <= 800)
	{
		prevLevel = level;
		level = 11;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 800 && l <= 900)
	{
		prevLevel = level;
		level = 12;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 900 && l <= 1050)
	{
		prevLevel = level;
		level = 13;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 1050 && l <= 1225)
	{
		prevLevel = level;
		level = 14;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else if (l >= 1225 && l <= 1500)
	{
		prevLevel = level;
		level = 15;
		newLevel = level;
		if (newLevel == prevLevel + 1)
			levelUpDisplay();
		cout << "You are currently a Level " << getLevel() << endl;
		prevLevel = newLevel = NULL;
	}
	else
	{
		cout << "You have reached the current level maximum of " << getLevel() << endl << endl;
	}

	return level;
}

int Player::getLevel()
{
	return level;
}

void Player::getStats()
{
	TreasureChest t1;
	cout << "Your current state are:" << endl;
	cout << "HP:\t\t" << getLife() << endl;
	cout << "XP:\t\t" << getXP() << endl;
	cout << "Level:\t\t" << getLevel() << endl;
	cout << "Defense:\t\t" << getDefense() << endl << endl;
	cout << "here is a list of your current inventory: " << endl;
	t1.Show();
}

int Player::getLife()
{
	return hp;
}

int Player::getXP()
{
	return xp;
}

int Player::getDefense()
{
	return defense;
}

void Player::levelUpDisplay()
{
	cout << "YOU LEVELED UP!!!" << endl;
}