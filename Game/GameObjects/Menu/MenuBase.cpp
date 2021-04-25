#include "MenuBase.h"

MenuBase::MenuBase()
{

}

MenuBase::~MenuBase()
{

}

void MenuBase::Initialise()
{
	// -------- Set the Positions -------- //
	m_MenuBackground.setPosition(450, 390);
	m_MenuLogo.setPosition(500, 150);

	// -------- Set Up the Animation Sprite Sheets XML -------- //
	pSpriteSheetDef1 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_background_data.xml");
	pSpriteSheetDef2 = pGameDataManager->GetSpritesheetDef("sprites/menu/spr_menu_logo_data.xml");

	// -------- Populate the Animation State -------- //
	m_MenuBackground.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef1, "spr_intro_animated", 7, true);
	m_MenuLogo.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef2, "spr_logo", 7, false);
	
	// -------- Set the Default Animation -------- //
	m_MenuBackground.SetCurrentAnimation(1);
	m_MenuLogo.SetCurrentAnimation(1);
}

void MenuBase::Update()
{
	m_MenuBackground.Animate();
	m_MenuBackground.setScale(1.2, 1.2);

	m_MenuLogo.Animate();
	m_MenuLogo.UIObject(false);
}

void MenuBase::GetPosition(int& x, int & y)
{
	m_MenuBackground.getPosition().x;
	m_MenuBackground.getPosition().y;
}