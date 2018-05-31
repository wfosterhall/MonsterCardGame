#include <stdlib.h>
#include <iostream>

#include "cardList.h"
#include "card.h"

using namespace std;

//max 30 card list constructor
cardList::cardList(string str){
	type = str;
	maxSize = 30;
}

//user defined max card list constructor
cardList::cardList(string str, int n){
	type = str;
	maxSize = n;
}

//get size function definition
int cardList::getSize(){
	return list.size();
}

//empty list function definition
bool cardList::isEmpty(){
	if (list.empty()){
		cout << type << " is empty."<< endl;
		return true;
	}
	return false;
}

//full list function definition
bool cardList::isFull(){
	if (list.size() >= maxSize){
		cout << type << " is full." << endl;
		return true;
	}
	return false;
}

//draw card function definition
card * cardList::drawCard(int i){
	// if we dont choose a specifc card return a random card from list.
	if (list.size() > 0) {
		if (i < 0) {
			i = rand() % list.size();
		}
		card * drawn = list[i];
		list.erase(list.begin()+i);
		return drawn;	
	}
	// if there are no cards remaining
	cout << "Deck is empty!" <<endl;
}

//add card function definition
void cardList::addCard(card* newCard){
	list.push_back(newCard);
}

//print card function definition
void cardList::printCard(int i){
	cout << list[i]->getName() << endl;
}

//print all function definition
void cardList::printAll(int OS){

	string TL, TR, BL, BR, V, H;

	// If statement as the cards need to be printed differently on different systems
	if (OS == 1){
		TL = (char)218;
		TR = (char)191;
		BL = (char)192;
		BR = (char)217;
		V = (char)179;
		H = (char)196;
	}
	else {

		TL = "┌";
		TR = "┐";
		BL = "└";
		BR = "┘";
		V = "|";
		H = "─";
	}
		for (int i = 0; i < list.size(); i++){
			cout << TL;
			for (int j = 0; j < 21; ++j){
				cout << H;
			}
			cout << TR;
		}
		cout << endl;

		//| ┌─────────────────┐ |

		for (int i = 0; i < list.size(); i++){
			cout << V << " " << TL;
			for (int j = 0; j < 17; j++){
				cout << H;
			}
			cout << TR << " " << V;
		}
		cout << endl;

		for (int i = 0; i < list.size(); i++){
			string name = list[i]->getName();
			cout << V << " " << V << " " << name;
			if (name.length() < 15) {
				for (int i = 0; i < 15 - name.length(); ++i){
					cout << " ";	
				}
			}
			cout << " " << V << " " << V;
		}
		cout << endl;

		for (int i = 0; i < list.size(); i++){
			cout << V << " " << BL;
			for (int j = 0; j < 17; ++j){
				cout << H;
			}
			cout << BR << " " << V;
		}
		cout << endl;

		//|                     |
		for (int i = 0; i < list.size(); i++){
			cout << V;
			for (int j = 0; j < 21; ++j){
				cout << " ";
			}
			cout << V;
		}
		cout << endl;

		//|                     |
		for (int i = 0; i < list.size(); i++){
			cout << V;
			for (int j = 0; j < 21; ++j){
				cout << " ";
			}
			cout << V;
		}
		cout << endl;

		//|                     |
		for (int i = 0; i < list.size(); i++){
			cout << V;
			for (int j = 0; j < 21; ++j){
				cout << " ";
			}
			cout << V;
		}
		cout << endl;

		//|   Atk        Def    |
		for (int i = 0; i < list.size(); i++){
			if (list[i]->getEffect() == 0)
			{
				cout << V << "   Atk        Def    " << V;
			}
			else
			{
				cout << V << "     Spell Card      " << V;
			}
		}
		cout << endl;

		for (int i = 0; i < list.size(); i++){
			cout << V << "   ";

			//if card is monster card print attack and defence stats
			if (list[i]->getEffect() == 0)
			{
				int atk = list[i]->getAttack();

				if (atk < 1000){
					cout << "0" << atk;
				}
				else {
					cout << atk;
				}
				cout << "       ";

				int def = list[i]->getDefence();
				if (def < 1000){
					cout << "0" << def;
				}
				else {
					cout << def;
				}
			}
			else
			{
				cout << "               ";
			}
			cout << "   " << V;
		}
		cout << endl;

		for (int i = 0; i < list.size(); i++){
			cout << BL;
			for (int j = 0; j < 21; ++j){
				cout << H;
			}
			cout << BR;
		}
		cout << endl;
}