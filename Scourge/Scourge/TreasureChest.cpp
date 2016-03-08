#include "TreasureChest.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

TreasureChest::TreasureChest() :size(0), head(NULL){};

TreasureChest::TreasureChest(TreasureChest &L) : size(L.size)
{
	if (L.head == NULL)
		head = NULL;
	else
	{
		head = new Item;
		head->data = L.head->data;
		Item *newPtr = head;
		//iterator to copy list
		for (Item *origPtr = L.head->next; origPtr != NULL; origPtr = origPtr->next)
		{
			newPtr->next = new Item;
			newPtr = newPtr->next;
			newPtr->data = origPtr->data;
		}
	}
}

TreasureChest::~TreasureChest()
{
	bool succ;
	while (!isListEmpty())
		Delete(1, succ);
}

int TreasureChest::ListLength()
{
	return size;
}

void TreasureChest::ListInsert(int position, Item data, bool succ)
{
	int newLength = ListLength() + 1;
	succ = bool((position >= 1) && (position <= newLength));
	if (succ)
	{
		Item *newPtr = new Item;
		succ = bool(newPtr != NULL);
		if (succ)
		{
			size = newLength;
			newPtr->data = data.data2;
			if (position == 1)
			{
				newPtr->next = head;
				head = newPtr;
			}
			else
			{
				Item *prev = PointTo(position - 1);
				newPtr->next = prev->next;
				prev->next = newPtr;
			}
		}
	}
}

void TreasureChest::Delete(int position, bool &succ)
{
	Item *ptr;
	succ = bool((position >= 1) && (position <= ListLength()));
	if (succ)
	{
		size--;
		if (size > 1)
		{
			if (position == 1)
			{
				ptr = head;
				head = head->next;
			}
			else
			{
				Item *temp = PointTo(position - 1);
				ptr = temp->next;
				temp->next = ptr->next;
			}
			ptr->next = NULL;
			delete ptr;
			ptr = NULL;
		}
		else if (size == 1)
		{
			if (position > 1)
			{
				Item *ptr = PointTo(position - 1);
				head->next = NULL;
				delete ptr;
				ptr = NULL;
				size--;
			}
		}
		else
		{
			cout << "====================================================================" << endl;
			cout << "===========================LIST IS EMPTY============================" << endl;
			cout << "====================================================================" << endl;
		}
	}
}

void TreasureChest::Retrieve(int position, Item &data, bool &succ)
{
	succ = bool((position > 1) && (position < ListLength()));
	if (succ)
	{
		Item *curr = PointTo(position);
		data.data = curr->data;
		delete curr;
		curr = NULL;
	}
}

void TreasureChest::Show()
{
	int i = 1;
	if (ListLength() != 0)
	{
		for (Item *curr = head; curr != NULL; curr = curr->next)
		{
			cout << "Item " << i << ":\t\t" << curr->data << endl;
			i++;
		}
	}
}

bool TreasureChest::isListEmpty()
{
	return bool(size == 0);
}

Item *TreasureChest::PointTo(int position)
{
	if ((position < 1) || (position > ListLength())) return NULL;
	else
	{
		Item *current = head;
		for (int skip = 1; skip < position; skip++)
			current = current->next;
		return current;
	}
}