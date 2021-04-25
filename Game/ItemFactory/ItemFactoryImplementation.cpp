#include "ItemFactoryImplementation.h"


#include "../Item/SpeedPickup.h"
#include "../Item/HealthPickup.h"

ItemFactoryImplementation::ItemFactoryImplementation()
{
}

ItemFactoryImplementation::~ItemFactoryImplementation()
{
}

void ItemFactoryImplementation::Initialize()
{
}

Item * ItemFactoryImplementation::make_item(int pint)
{

	//Switch statement which changes what item is created depending on the int provided;
	switch (pint)
	{

		
	case SPEED_PICKUP:
		m_speed = new SpeedPickup(1500, 1500);
		return m_speed;
		

	case HEALTH_PICKUP:
		m_health = new HealthPickup(1000, 1000);
		return m_health;
		

	default:
		return nullptr;
	
	}
}
