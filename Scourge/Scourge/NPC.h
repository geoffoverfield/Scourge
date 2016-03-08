#ifndef NPC_H
#define NPC_H
#include <iostream>
#include <ctime>
#include <cmath>
#include "BOSS.h"
#include "OperatorOverload.h"
using namespace std;

class NPC : public OperatorOverload<NPC>
{
public:
	
	int rep;
	string name;
	string Name(int);
	string NPC_Names[20];
	NPC()
	{
		rep = 10;
		srand(time(NULL));
		int num = rand() % 20;
		Name(num);
	}
private:
};

#endif