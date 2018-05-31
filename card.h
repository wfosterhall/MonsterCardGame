#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

//card class definition
class card {

protected:
	string name;
	int attack;
	int defence;
	int effect;

public:
	card(string str, int atk, int def, int eff);
	string getName();
	int getAttack();
	int getDefence();
	int getEffect();
	void setAttack(int atk);
	void setDefense(int def);

	virtual bool doEffect();

	virtual ~card();

};

#endif