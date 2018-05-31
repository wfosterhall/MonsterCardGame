#include <string.h>

#include "spellCard.h"

spellCard::spellCard(string str, int eff) : card(str, 0, 0, eff)
{
	name = str;
	effect = eff;

}


bool spellCard::doEffect(cardList* field1, cardList* field2, cardList* grave1, cardList* grave2)
{

	switch (effect)
	{

		case 1:
			clearField(field1, grave1);
			clearField(field2, grave2);
			break;
	}



}


bool spellCard::clearField(cardList * field, cardList * grave)
{
	while (!field->isEmpty())
	{
		card* played = field->drawCard(-1);
		grave->addCard(played);

	}
}

spellCard::~spellCard()
{
	
}


