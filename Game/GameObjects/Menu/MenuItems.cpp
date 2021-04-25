#include "MenuItems.h"

#include "../Player/AttributeHandler.h"

MenuItems::MenuItems()
{

}

MenuItems::~MenuItems()
{

}

void MenuItems::Initialise()
{
	pAttributeHandler->GameRestart = false;
	
	// -------- Set the Positions -------- //
	m_StartButton.setPosition(500, 350);
	m_ExitButton.setPosition(500, 450);

	// -------- Set Up the Animation Sprite Sheets XML -------- //
	pSpriteSheetDef1 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_start_data.xml");
	pSpriteSheetDef2 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_exit_data.xml");
	
	// -------- Start Button Anims -------- //
	m_StartButton.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef1, "spr_menu_open", 1, false);
	m_StartButton.AddAnimationFromSpriteSheetDef(2, pSpriteSheetDef1, "spr_menu_selected", 1, false);

	// -------- Exit Button Anims -------- //
	m_ExitButton.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef2, "spr_menu_exit", 1, false);
	m_ExitButton.AddAnimationFromSpriteSheetDef(2, pSpriteSheetDef2, "spr_menu_selected", 1, false);

	// -------- Controls Sprite -------- //
	m_Controls.Initialise("sprites/menu/spr_controls_menu.png", 0, 0, 1, 1, false);

	// -------- Set the Default Animation -------- //
	m_StartButton.SetCurrentAnimation(2);
	m_ExitButton.SetCurrentAnimation(1);
}

void MenuItems::Update()
{
	m_StartButton.Animate();
	m_StartButton.UIObject(false);

	m_ExitButton.Animate();
	m_ExitButton.UIObject(false);
	
	// -------- Button Selection Logic -------- //
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )//&& pAttributeHandler->GameRestart == false)
	{
		if (m_StartButton.GetCurrentAnimation() == 2)
		{
			pGameStateManager->QueuePop();
		}
		else if (m_ExitButton.GetCurrentAnimation() == 2)
		{
			exit(0);
		}
	}

	// -------- Menu Button Anim Update -------- //
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_StartButton.GetCurrentAnimation() == 2)
		{
			m_StartButton.SetCurrentAnimation(1);
			m_ExitButton.SetCurrentAnimation(2);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_ExitButton.GetCurrentAnimation() == 2)
		{
			m_StartButton.SetCurrentAnimation(2);
			m_ExitButton.SetCurrentAnimation(1);
		}
	}
}

void MenuItems::GetPosition(int& x, int & y)
{
	m_StartButton.getPosition().x;
	m_StartButton.getPosition().y;
}