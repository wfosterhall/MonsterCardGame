#ifndef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include <string>

#include "card.h"

//cardlist class defintion
class cardList{
	std::vector<card*> list;
	int maxSize;
	//put a name for the list in here, such as hand or field
	string type;

public:
	cardList(string str);
	cardList(string str,  int n);
	card * drawCard(int i);
	void addCard(card* newCard);
	void printCard(int i);
	void printAll(int OS);
	int getSize();
	bool isEmpty();
	bool isFull();
};

#endif