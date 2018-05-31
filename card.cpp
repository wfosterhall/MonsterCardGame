#include <string>
#include "card.h"

using namespace std;

//card constructor
card::card(string str, int atk, int def, int eff){
	name = str;
	attack = atk;
	defence = def;
	effect = eff;
}

//get name function definition
string card::getName(){
	if (!name.empty()){
		return name;
	}
}

//get attack function definition
int card::getAttack(){
	return attack;
}

//get defence function definition
int card::getDefence(){
	return defence;
}

//get effect function defintion
int card::getEffect(){
	return effect;
}

bool card::doEffect (){
	
}

card::~card(){
}