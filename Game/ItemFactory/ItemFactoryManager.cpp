#include "ItemFactoryManager.h"

ItemFactoryManager::ItemFactoryManager()
{
}

ItemFactoryManager::~ItemFactoryManager()
{
}

ItemFactory* ItemFactoryManager::GetFactory()
{
	return m_pItemFactory;
}

void ItemFactoryManager::SetFactory(ItemFactory* p_item_factory)
{
	m_pItemFactory = p_item_factory;
}

void ItemFactoryManager::Initialise()
{
}