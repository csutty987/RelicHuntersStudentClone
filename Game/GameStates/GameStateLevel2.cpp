#include "GameStateLevel2.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"
#include <iostream>

GameStateLevel2::GameStateLevel2()
{

}

GameStateLevel2::~GameStateLevel2()
{

}


void GameStateLevel2::Initialise()
{
	//--------------------------------------------------------//

	m_Tilemap_Floor_02 = new TileMap();
	m_Tilemap_Floor_02->Initialise();
	m_Tilemap_Floor_02->LoadFromFile("levels/TileMap_Floor_02.txt");
	m_GameObjects.push_back(m_Tilemap_Floor_02);

	//--------------------------------------------------------//

	m_Tilemap_Wall_02 = new TileMap();
	m_Tilemap_Wall_02->Initialise();
	m_Tilemap_Wall_02->LoadFromFile("levels/TileMap_Wall_02.txt");
	m_GameObjects.push_back(m_Tilemap_Wall_02);

	//--------------------------------------------------------//

	//Initialise Player
	m_Player = new Player();
	m_Player->Initialise();
	m_GameObjects.push_back(m_Player);

	//Initialise Camera
	m_Camera = new Camera();
	m_Camera->Initialise();
	m_GameObjects.push_back(m_Camera);

	std::vector<sf::Vector2i> tpositions;
	tpositions.push_back(sf::Vector2i(100, 400));
	tpositions.push_back(sf::Vector2i(350, 900));
	tpositions.push_back(sf::Vector2i(1900, 650));
	tpositions.push_back(sf::Vector2i(150, 1500));
	tpositions.push_back(sf::Vector2i(1800, 1050));

	std::vector<bool> tDirections;
	tDirections.push_back(true);
	tDirections.push_back(true);
	tDirections.push_back(false);
	tDirections.push_back(true);
	tDirections.push_back(false);

	for (int i = 0; i < tpositions.size(); i++)
	{
		Enemy01* m_Enemy = new 	Enemy01();
		m_Enemy->SetDirection(tDirections[i]);
		m_Enemy->Initialise();
		m_Enemy->SetPosition(tpositions[i].x, tpositions[i].y);
		this->m_pEnemies.push_back(m_Enemy);
		this->m_GameObjects.push_back(m_Enemy);

	}

	// -------- Enemy02 positions -------- //
	std::vector<sf::Vector2i> e2_positions;
	e2_positions.push_back(sf::Vector2i(100, 500));
	e2_positions.push_back(sf::Vector2i(500, 1000));
	e2_positions.push_back(sf::Vector2i(2000, 650));
	e2_positions.push_back(sf::Vector2i(300, 1180));

	// -------- Initialise Enemy02 -------- //

	for (int i = 0; i < e2_positions.size(); i++)
	{
		Enemy_02* m_Enemy = new Enemy_02();
		m_Enemy->Initialise();
		m_Enemy->SetPosition(e2_positions[i].x, e2_positions[i].y);
		this->m_pEnemies.push_back(m_Enemy);
		this->m_GameObjects.push_back(m_Enemy);

	}

	//--------------------------------------------------------//

	m_HudBase = new HudBase();
	m_HudBase->Initialise();
	m_GameObjects.push_back(m_HudBase);

	//--------------------------------------------------------//

	m_ItemManager = C_SysContext::Get<ItemFactoryManager>();
	m_Items.push_back(m_ItemManager->GetFactory()->make_item(1));

	Item* t_item = m_Items.front();

	t_item->Initialise();

}

void GameStateLevel2::Update()
{
	GameState::Update();

	//BG Music
	if (musicPlaying == false)
	{
		AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();

		pAudioManager->PlayMusic("sounds/bgm_menu.wav");
		musicPlaying = true;
	}
	
	int x, y;
	this->m_Player->GetPosition(x, y);
	int tilenum = m_Tilemap_Wall_02->TileIndexAtPosition(x, y);
	m_Player->SetPlayerTileNum(tilenum);

	int uptilenum = m_Tilemap_Wall_02->TileIndexAtPosition(x, (y + 1));
	int downtilenum = m_Tilemap_Wall_02->TileIndexAtPosition(x, (y - 1));
	int lefttilenum = m_Tilemap_Wall_02->TileIndexAtPosition((x - 1), y);
	int righttilenum = m_Tilemap_Wall_02->TileIndexAtPosition((x + 1), y);
	m_Player->SetSurroundingTileNum(uptilenum, downtilenum, lefttilenum, righttilenum);

	// -------- Switch to Next Level --------
	if (m_Player->PlayerScore == 700)
	{
		pGameStateManager->QueuePop();
		pAttributeHandler->ScoreValue = 1400;
	}
	else if (pAttributeHandler->isDead == true || m_Player->isDead == true)
	{
		pAttributeHandler->ScoreValue = m_Player->PlayerScore + 700;
		pAttributeHandler->isDead = true;
		pGameStateManager->QueuePop();
	}
	
}

Player *GameStateLevel2::DetailedGetPlayer()
{
	return m_Player;
}


GameObject *GameStateLevel2::GetPlayer()
{
	return m_Player;
}

GameObject *GameStateLevel2::GetBullet()
{
	return m_Bullet;
}