#pragma once
#include "ItemFactory.h"

class ItemFactoryImplementation:
public ItemFactory
{
public:
	ItemFactoryImplementation();
	~ItemFactoryImplementation() override;
	
	void Initialize();

	//Creates the function
	Item* make_item(int pint) override;

//Enum to assign each pickup to a number
protected:
	enum items
	{
		
		SPEED_PICKUP,
		HEALTH_PICKUP,
	};

	//pointers to the item class which will then be used to polymorphically create the specific item classes.
	Item* m_speed;
	Item* m_health;
};



