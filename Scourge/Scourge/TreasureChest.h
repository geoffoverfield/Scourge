#ifndef TREASURECHEST_H
#define TREASURECHEST_H
#include "Item.h"
using namespace std;

class TreasureChest
{
public:
	TreasureChest();
	TreasureChest(TreasureChest &);		//Copy Contructor
	~TreasureChest();					//Destructor
	int ListLength();
	void ListInsert(int, Item, bool);
	void Delete(int, bool &);
	void Retrieve(int, Item &, bool &);
	void Show();
	bool isListEmpty();
private:
	Item *head;
	int size;
	Item *PointTo(int);
};


#endif