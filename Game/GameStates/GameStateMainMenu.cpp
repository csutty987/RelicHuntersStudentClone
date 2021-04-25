#include "GameStateMainMenu.h"

GameStateMainMenu::GameStateMainMenu()
{

}

GameStateMainMenu::~GameStateMainMenu()
{

}

void GameStateMainMenu::Update()
{
	GameState::Update();
}

void GameStateMainMenu::Initialise()
{
	// -------- Menu Base -------- //
	m_MenuBase = new MenuBase();
	m_MenuBase->Initialise();
	m_GameObjects.push_back(m_MenuBase);

	// -------- Menu Items -------- //
	m_MenuItems = new MenuItems();
	m_MenuItems->Initialise();
	m_GameObjects.push_back(m_MenuItems);

	// -------- Initialise Player -------- //
	m_Player = new Player();

	pAttributeHandler->GameRestart = false;

}

GameObject *GameStateMainMenu::GetPlayer()
{
	return m_Player;
}

GameObject *GameStateMainMenu::GetBullet()
{
	return m_Bullet;
}

Player *GameStateMainMenu::DetailedGetPlayer()
{
	return m_Player;
}
