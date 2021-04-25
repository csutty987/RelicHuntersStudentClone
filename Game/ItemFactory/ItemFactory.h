#pragma once
#include "../../Application/Project5110/Source/Game/Item/Item.h"
class ItemFactory
{
public:
	ItemFactory();
	virtual ~ItemFactory();

	void Initialise();
	
	//Creates the item
	virtual Item* make_item(int pint);
};

