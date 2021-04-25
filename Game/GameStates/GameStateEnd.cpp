#include "GameStateEnd.h"

GameStateEnd::GameStateEnd()
{

}

GameStateEnd::~GameStateEnd()
{

}

void GameStateEnd::Initialise()
{
	// -------- Menu Base -------- //
	m_MenuBase = new MenuBase();
	m_MenuBase->Initialise();
	m_GameObjects.push_back(m_MenuBase);

	// -------- Set the Positions -------- //
	m_ReturnButton.setPosition(500, 500);
	m_ExitButton.setPosition(500, 650);

	// -------- Set Up the Animation Sprite Sheets XML -------- //
	pSpriteSheetDef1 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_return_data.xml");
	pSpriteSheetDef2 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_exit_data.xml");

	// -------- Return Button Anims -------- //
	m_ReturnButton.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef1, "spr_menu_open", 1, false);
	m_ReturnButton.AddAnimationFromSpriteSheetDef(2, pSpriteSheetDef1, "spr_menu_selected", 1, false);

	// -------- Exit Button Anims -------- //
	m_ExitButton.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef2, "spr_menu_exit", 1, false);
	m_ExitButton.AddAnimationFromSpriteSheetDef(2, pSpriteSheetDef2, "spr_menu_selected", 1, false);

	// -------- Set the Default Animation -------- //
	m_ReturnButton.SetCurrentAnimation(2);
	m_ExitButton.SetCurrentAnimation(1);

	// -------- Initialise Player -------- //
	m_Player = new Player();
}

void GameStateEnd::Update()
{
	GameState::Update();
	
	m_ReturnButton.Animate();
	m_ReturnButton.UIObject(false);

	m_ExitButton.Animate();
	m_ExitButton.UIObject(false);

	// -------- End Screen Text -------- //
	if (pAttributeHandler->isDead == true)
	{
		m_YouWinText.Initialise("fonts/8-BIT WONDER.ttf", "JEEZ YOU SUCK", 35, 310, 270, sf::Color::White, false);
		m_MainText.Initialise("fonts/8-BIT WONDER.ttf", "Your Score", 35, 350, 340, sf::Color::White, false);
		UpdatePlayerScore(pAttributeHandler->ScoreString);
		for (i; i < 1; i++)
		{
			gAudioManager->PlaySoundFX("sounds/sfx_duck_death.wav", false);
		}
	}
	else
	{
		m_YouWinText.Initialise("fonts/8-BIT WONDER.ttf", "You Win", 35, 400, 270, sf::Color::White, false);
		m_MainText.Initialise("fonts/8-BIT WONDER.ttf", "Your Score", 35, 350, 340, sf::Color::White, false);
		UpdatePlayerScore(pAttributeHandler->ScoreString);
		for (i; i < 1; i++)
		{
			gAudioManager->PlayMusic("sounds/bgm_menu.wav");
		}
	}

	// -------- Button Selection Logic -------- //
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (m_ReturnButton.GetCurrentAnimation() == 2)
		{
			//Next GameState
			pAttributeHandler->GameRestart = true;
			//pGameStateManager->QueuePop();
		}
		else
		{
			//Exit Application
			exit(0);
		}
	}

	// -------- Menu Button Anim Update -------- //
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_ReturnButton.GetCurrentAnimation() == 2)
		{
			m_ReturnButton.SetCurrentAnimation(1);
			m_ExitButton.SetCurrentAnimation(2);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_ReturnButton.GetCurrentAnimation() == 1)
		{
			m_ReturnButton.SetCurrentAnimation(2);
			m_ExitButton.SetCurrentAnimation(1);
		}
	}
}

void GameStateEnd::UpdatePlayerScore(std::string Score)
{
	m_PlayerScore.Initialise("fonts/8-BIT WONDER.ttf", Score, 35, 450, 380, sf::Color::White, false);
}


GameObject *GameStateEnd::GetPlayer()
{
	return m_Player;
}

GameObject *GameStateEnd::GetBullet()
{
	return m_Bullet;
}

Player *GameStateEnd::DetailedGetPlayer()
{
	return m_Player;
}
