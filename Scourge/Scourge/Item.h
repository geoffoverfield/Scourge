#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "OperatorOverload.h"
using namespace std;

struct Item : public OperatorOverload<Item>
{
	string data;
	int data2;
	Item *next;
	Item()
	{
		next = NULL;
	}
};

#endif