#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "cardList.h"
#include "card.h"
#include "spellCard.h"

using namespace std;

void clearWindow();
void loadDeck(cardList * deck, string name);
void printLogo();

/* main game function */
int main()
{

	//Allocate game variables onto the stack
	int buffer = 0;
	int OS = 0;
	int lifePoints = 4000;
	int oppPoints = 4000;
	bool playTurn = false;

	printLogo();

	cout << "Are you using Linux (0) or Windows (1)" << endl;
	cin >> OS;

	cout << "Press 1 for random game, or 0 for non random" << endl;
	cin >> buffer;
	
	//if user selects random
	if (buffer == 1)
	{
		srand(time(NULL));
	}

	//create cardlist objects and allocate them on the heap
	cardList * oppDeck = new cardList("Opponents deck");
	cardList * deck = new cardList("Your deck");
	cardList * oppHand = new cardList("Opponents hand");
	cardList * hand = new cardList("Your hand", 5);
	cardList * field = new cardList("Field", 3);
	cardList * oppField = new cardList("Field", 3);
	cardList * graveyard = new cardList("Graveyard");
	cardList * oppGraveyard = new cardList("Opponents Graveyard");

	cout << "Select your deck: " << endl;
	cout << "  " <<"Yugi" << "     " << "Kaiba" << "     " << "Joey" << endl;
	cout << "   " << "[1]" << "      " << "[2]" << "       " << "[3]" << endl;
	cin >> buffer;

	//switch case depending on user input
	switch (buffer){
		case 1:
			loadDeck(deck, "Yugi");
			break;

		case 2:
			loadDeck(deck, "Kaiba");
			break;

		case 3:
			loadDeck(deck, "Joey");
			break;
	}

	//load deck for opponent
	//loadDeck(oppDeck, "Kaiba");

	cout << "Select your opponents deck: " << endl;
	cout << "  " <<"Yugi" << "     " << "Kaiba" << "     " << "Joey" << endl;
	cout << "   " << "[1]" << "      " << "[2]" << "       " << "[3]" << endl;
	cin >> buffer;

	//switch case depending on user input
	switch (buffer){
		case 1:
			loadDeck(oppDeck, "Yugi");
			break;

		case 2:
			loadDeck(oppDeck, "Kaiba");
			break;

		case 3:
			loadDeck(oppDeck, "Joey");
			break;
	}


	//draw 3 cards from deck to hand
	for (int i = 0; i < 3; ++i){
		card* drawn = deck->drawCard(-1);
		hand->addCard(drawn);
		card* oppDrawn = oppDeck->drawCard(-1);
		oppHand->addCard(oppDrawn);
	}

	//loop until user quits or game ends
	while (1)
	{
		clearWindow();

		//DRAW PHASE
		cout << "DRAW PHASE" << endl << endl;
		cout << "You have: " << lifePoints << " life points remaining" << endl;
		cout << "Your opponent has: " << oppPoints << " life points remaining" << endl;
		cout << "hand: " <<endl;
		hand->printAll(OS);
		cout << endl;
		cout << "There are " << deck->getSize() << " cards left in your deck." << endl;
		cout << "Press [1] to draw a card, [2] to check your graveyard, [3] to check opponents graveyard or [0] to quit." << endl;
		cin >> buffer;

		//switch case depending on user input
		switch (buffer){
			//press 0 to exit
			case 0:
				exit(EXIT_FAILURE);
			//press 1 to draw card
			case 1:
				if (!deck->isEmpty() && !hand->isFull()){
					card* drawn = deck->drawCard(-1);
					cout << "You drew " << drawn->getName() << endl;
					hand->addCard(drawn);
					cout << "Press any number." << endl;
					cin >> buffer;
				}
				else{
					cout << "Press any number." << endl;
					cin >> buffer;
				}
				playTurn = true;
				break;
			//press 2 to print user graveyard
			case 2:
				cout << "Graveyard: " << endl;
				graveyard->printAll(OS);
				cout << "Press any number." << endl;
				cin >> buffer;
				break;
			//press 3 to print opponent graveyard
			case 3:
				cout << "Opponents graveyard: " << endl;
				oppGraveyard->printAll(OS);
				cout << "Press any number." << endl;
				cin >> buffer;
				break;
		}
		//if user plays a card
		if (playTurn){
			card* oppDrawn = oppDeck->drawCard(-1);
			oppHand->addCard(oppDrawn);
			clearWindow();
			//print opponents field, users field and hand
			cout << "Opponents Field: " << endl;
			oppField->printAll(OS);
			cout << "Field: " << endl;
			field->printAll(OS);
			cout << "Hand: " << endl;
			hand->printAll(OS);
			//display numbers under each card in hand
			for (int i = 1; i <= hand->getSize(); ++i)
			{
				cout << "          " << "[" << i << "]" << "          ";
			}
			cout << endl;
			cout << "Choose a card to play" << endl;
			cin >> buffer;
			//if user chooses a card in hand
			if ((buffer > 0) && (buffer <= hand->getSize()))
			{
				//if hand is not empty field is not full
				if (!hand->isEmpty() && !field->isFull()){
					card* drawn = hand->drawCard(buffer-1);
					//if card played is a monster
					if (drawn->getEffect() == 0){
						field->addCard(drawn);
					}
					//if card played is a spell
					if (drawn->getEffect() == 1){
						spellCard * temp = dynamic_cast<spellCard*>(drawn);
						temp->doEffect(oppField, field, oppGraveyard, graveyard);
					}			
				}
				else{
					cout << "Press any number." << endl;
					cin >> buffer;
				}
			}
			//if opponent field is not full
			if (!oppHand->isEmpty() && !oppField->isFull()){
					card* oppCard = oppHand->drawCard(-1);
					//if opponent plays a monster card
					if (oppCard->getEffect() == 0){
						oppField->addCard(oppCard);
						cout << "Your opponent played " << oppCard->getName() << endl;
						cout << "Press any number." << endl;
						cin >> buffer;
					}
					//if opponent plays a spell card
					if (oppCard->getEffect() == 1){
						spellCard * temp = dynamic_cast<spellCard*>(oppCard);
						temp->doEffect(oppField, field, oppGraveyard, graveyard);
						oppGraveyard->addCard(oppCard);
						cout << "Your opponent played " << oppCard->getName() << endl;
						cout << "Press any number." << endl;
						cin >> buffer;
					}
				}
			//print out battle phase and both fields
			cout << "BATTLE PHASE" << endl;
			cout << "Opponents Field: " << endl;
			oppField->printAll(OS);

			for (int i = 1; i <= oppField->getSize(); ++i){
				cout << "          " << "[" << i << "]" << "          ";
			}
			cout << endl;

			cout << "Field: " << endl;
			field->printAll(OS);

			for (int i = 1; i <= field->getSize(); ++i){
				cout << "          " << "[" << i << "]" << "          ";
			}
			cout << endl;

			int mon = 0;
			int oppMon = 0;
			cout << "Choose a monster to attack with or [0] to not attack" << endl;
			cin >> mon;
				//if user chooses a monster on their field
				if ((mon > 0) && (mon <= field->getSize())){
				card* yugiMon = field->drawCard(mon-1);
				cout << "Choose opponents monster to attack or [0] to not attack" << endl;
				cin >> oppMon;
					//if user chooses one of opponents monsters to attack
					if ((oppMon > 0) && (oppMon <= oppField->getSize())){
						card* kaibaMon = oppField->drawCard(oppMon-1);
						//if attack of user monster is more than opponents
						if (yugiMon->getAttack() > kaibaMon->getAttack()){
							oppGraveyard->addCard(kaibaMon);
							field->addCard(yugiMon);
							oppPoints = oppPoints - (yugiMon->getAttack()-kaibaMon->getAttack());
							cout << "You attacked " << kaibaMon->getName() << " with " << yugiMon->getName() << " and sent it to the graveyard." << endl;
							cout << "Press any number." << endl;
							cin >> buffer;
						}
						//if attack value of user monster is less or equal to opponents
						else if (yugiMon->getAttack() <= kaibaMon->getAttack()){
							graveyard->addCard(yugiMon);
							oppField->addCard(kaibaMon);
							lifePoints = lifePoints - (kaibaMon->getAttack()-yugiMon->getAttack());
							cout << "You attacked " << kaibaMon->getName() << " with " << yugiMon->getName() << " and sent themselves to the graveyard." << endl;
							cout << "Press any number." << endl;
							cin >> buffer;
						}
					}
					//if opponent has no monsters on field attack them directly
					else if ((oppMon > 0) && (oppField->getSize() == 0)){
						oppPoints = oppPoints - yugiMon->getAttack();
						field->addCard(yugiMon);
						cout << "You attacked your opponent directly with " << yugiMon->getName() << " and dealt " << yugiMon->getAttack() << " damage to their life points." << endl;
						cout << "Press any number." << endl;
						cin >> buffer;
					}
					else
					{
						field->addCard(yugiMon);
					}
				}
				//if opponent has a monster on the field and user does
				if ((oppField->getSize() != 0) && (field->getSize() != 0)){
					card* attacker = oppField->drawCard(-1);
					card* defender = field->drawCard(-1);
					//if user monster has less attack than opponent send users to their graveyard
					if (attacker->getAttack() > defender->getAttack()){
						graveyard->addCard(defender);
						oppField->addCard(attacker);
						lifePoints = lifePoints - (attacker->getAttack()-defender->getAttack());
						cout << "Your opponent attacked " << defender->getName() << " with " << attacker->getName() << " and sent it to the graveyard." << endl;
						cout << "Press any number." << endl;
						cin >> buffer;
					}
					//if user monster has more attack than opponent send opponenets to their graveyard
					else if (attacker->getAttack() < defender->getAttack()){
						oppGraveyard->addCard(attacker);
						field->addCard(defender);
						oppPoints = oppPoints - (defender->getAttack()-attacker->getAttack());
						cout << "Your opponent attacked " << defender->getName() << " with " << attacker->getName() << " and sent themselves to the graveyard." << endl;
						cout << "Press any number." << endl;
						cin >> buffer;
					}
				}
				//if opponent has a monster on the field and user does not
				else if ((oppField->getSize() != 0) && (field->getSize() == 0)){
					card* attacker = oppField->drawCard(-1);
					lifePoints = lifePoints - attacker->getAttack();
					oppField->addCard(attacker);
					cout << "Your opponent attacked you directly with " << attacker->getName() << " and dealt " << attacker->getAttack() << " damage to your life points." << endl;
					cout << "Press any number." << endl;
					cin >> buffer;
				}
				//when user hits 0 life points user lost and game ends
				if (lifePoints <= 0){
					cout << "You have: " << lifePoints << " life points remaining" << endl;
					cout << "Your opponent has: " << oppPoints << " life points remaining" << endl;
					cout << "You lost!" << endl;
					cout << "Press any number." << endl;
					cin >> buffer;
					exit(EXIT_FAILURE);
				}
				//when opponent hits 0 life points user won and game ends
				else if (oppPoints <= 0){
					cout << "You have: " << lifePoints << " life points remaining" << endl;
					cout << "Your opponent has: " << oppPoints << " life points remaining" << endl;
					cout << "You won!" << endl;
					cout << "Press any number." << endl;
					cin >> buffer;
					exit(EXIT_FAILURE);
				}
			playTurn = false;
		}
	}
}

/* function to space out command window */
void clearWindow(){
	for (int i = 0; i < 40; i++){
		cout << endl;
	}
}

/* function to load deck list from dat file */
void loadDeck(cardList * deck, string deckName){
	string name;
	int atk;
	int def;
	int eff;
	string dir = deckName + ".dat";
	ifstream file(dir.c_str());
	string input;

	//loop through each line in the dat file
	while (getline(file, input)){
		int j = 0;
		for (int i = 0; i < 4; ++i){
			string value;
			while(input[j] != ','){
				if (input[j]) {
				value.push_back(input[j]);
				j++;
				}
				else {
					break;
				}
			}
			j++;

			//take card name from first word, attack value from second, defence value from third and effect from fourth
			switch (i){
				case 0 :
					name = value;
					break;

				case 1 :
					atk = atoi((value).c_str());
					break;

				case 2 :
					def = atoi(value.c_str());
					break;

				case 3 :
					eff = atoi(value.c_str());
					break;
			}
		}
		//add card to the deck

		if (eff == 0)
		{
			card * temp = new card(name, atk, def, eff);
			deck->addCard(temp);
		}
		else
		{
			spellCard * temp = new spellCard(name, eff);
			deck->addCard(temp);
		}
	}
}
/*function to print main logo*/
void printLogo(){
	cout << "                                                                                                                                                               " << endl <<
			"                                                                                                                                                               " << endl <<
			"                         ###                                                                                                                                   " << endl <<
			"                        #####*        ####                                         ###                                                                         " << endl <<
			"                        #####        #####                    #################    ####           #                .##################((*.                     " << endl <<
			"        (#####         ###        *###############           ####################  ####     ######               ################################(             " << endl <<
			"     ########.    ,#########,    #################             .#############*     ####      #####              #################################              " << endl <<
			"     #####*     ################           .#####                    ###            ####                         ###############################               " << endl <<
			"               ###///////////////.,#/////////////           #####*@################ ####   .,/#(@/#*.     .*#/@(.,/@@#**/(((/**#@@/#                           " << endl <<
			"                 #/@@*........,@@#/@/.,..,,.../@#.          ###/@@,@@/#&@@@/@@@(##   #%%#&@@@@@*,@@@@@@@@@@@@@@#. ,(@@,........@@(#,                           " << endl <<
			"         #####    ,/#(@@@@@@,*@%#*(##@@@@@@@@/#*.           */@@((@#,*%#@/(@(,.@@/#####*@@...@@&@@@*,,./@@../@@#.  ,/@@@@,.,((@@###                            " << endl <<
			"      #######        ###@@&@@,,@//,#@@%&&@###             .#@@//&/@(@@/(@@/@@@@&/@/#####@@@@,*@@@@@@#./@@@*,*@@#.   **@*@@*(,#@/###                            " << endl <<
			"     ####(          ####//@@&@,.@@/@/%&&@##              ,#@@,%(*@//@@@,@//@/@/@*/(#  ##@@@@,,@/#@@@@./@(@@,.@@#.    #@@@@/**@%#################               " << endl <<
			"                  #####  .#@@%@@,*&%&/@###############/**#@@@&/ @//./#&@@////@////////##@@@@.,@/#@@@@./@(@@.(@@#*/#####@/@,./@@/###############                " << endl <<
			"          ####   ####     ##/@@@@,#%@(#.,,%@&,.,.@@@@@@@@@@/@@,*@##%@@@//*(,.,,&/@@@@@@@@(%%@/@/#@@@@,,@(@@,.@@@@@%@@##@#@@(/@################                 " << endl <<
			"        #####  #####    #####*@*@&,/@@#@**%@&@@..@@/%,..@@@#@@, @@@*(/,,.@@@@,,@@/(,,,&/@@@@(*@/#@@@*,,@(@@..@/,,*/@@##/@@@#@/##### ( #*                       " << endl <<
			"      #####.  ####     #####**@*@&*/@@#@,,%@&@@,*@@@@@@@@@@@@@,,/@%*@@@*(@@@@, @@@@@@@@@@@@@**@/#@@@@*/@(@@..@@@@,/@@##/@@@/@######                            " << endl <<
			"     ####            /##### **@*@&,/@@#@,*%@&@@**@@#(#####@@@@@..@@@(&&,*@@@@,,@@##((##@@&@@,*@/#@@@@#%@(@@.*@@@@./@@@@@@@@(/######                            " << endl <<
			"           .#(      ######  **@*@&,/@@#@,.%@/@@, @@#@@@####@@@@@,,//&%,,*@@@@,(@@#.   .#@@@(@.@@@@@@@@(@@*/@@@@,/@(@(&@@@@/######                            " << endl <<
			"          ###      #####    /*@*@&*/@@#@#,,,@@@,,@@@,/@(   *(@@/@@,.@@@*(@@@@,,@@#.    ##/@@@(@,(,@@@@@@(@@./@@@@,,#/%/@@,,,/@@####                            " << endl <<
			"        *################(/#%@/*@@@,/@@(@@@&@%@@,..@@@#,    .#@@@&@@@@@@.@@@@@,@@#.  ###  ##@@@&&@@@@@@@/@@#/@@@@@&@(@@@*@@@@@@@@(######,                      " << endl <<
			"      (################(%@@@@@@@@@@@@@@@@@@@@@#@@@%@@#.       */@@@@@@@@@@@@@@@@@#. ###    ###@@@@@/@@@@@@@@@@@@@/(@@@#/@@%@@@##################               " << endl <<
			"     ##################################(////#*@@@@@#,          ##@@/#############. ###      ###(@###////////####/@@####/@/######%@#########################  " << endl <<
			"    #########        ,###########################*((    ##,,####################  ##,       #################################################################  " << endl <<
			"     ####                     ###########################, ###########           /#          #############################//#* ,  ,#########################   " << endl <<
			"                                  ######################   ###                                ############ #######                        ################     " << endl <<
			"                                     #################                                        ##########    ,###                              ##########       " << endl <<
			"                                       #############                                           #######                                           ####          " << endl <<
			"                                         ,#####,                                                                                                               " << endl <<
			"                                                                                                                                                               " << endl;
}