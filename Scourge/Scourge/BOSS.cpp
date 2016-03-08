#include "BOSS.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
using namespace std;

BOSS::BOSS()
{
	HP = 100 * level;
	AP = 20 * level;
	DP = 15 * level;
	attack = defend = false;
}

int BOSS::Attack(int a)
{
	int attk = a;
	__asm
	{
		mov eax, attk
			mov ebx, a
			add eax, ebx
			mov attk, eax
	}
	attk = attk + Bonus();
	return attk;
}

int BOSS::Defend(int d)
{
	int dfnd = d;
	__asm
	{
		mov eax, dfnd
		mov ebx, d
		add eax, ebx
		mov dfnd, eax
	}
	dfnd = dfnd + Bonus();
	return dfnd;
}

int BOSS::Bonus()
{
	srand(time(NULL));
	int bonus = rand() % 10;
	return bonus;
}

int BOSS::getLife()
{
	return HP;
}