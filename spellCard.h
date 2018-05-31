#include "card.h"
#include "cardList.h"

class spellCard : public card {
	
	bool clearField(cardList* field, cardList* grave);

	public:
		spellCard(string str, int effect);

		bool doEffect(cardList* field1, cardList* field2, cardList* grave1, cardList* grave2);

		virtual ~spellCard();

};