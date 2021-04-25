#pragma once

#include <vector>


#include "ItemFactoryImplementation.h"

class ItemFactoryManager
{
public:
	ItemFactoryManager();
	~ItemFactoryManager();

	void Initialise();

	ItemFactory* GetFactory();
	void SetFactory(ItemFactory* p_item_factory);

protected:
	ItemFactory* m_pItemFactory;
       
};

