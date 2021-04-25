#include "HudBase.h"

HudBase::HudBase()
{

}

HudBase::~HudBase()
{

}

void HudBase::Initialise()
{
	// -------- Hud Background Creation -------- // 
	m_HudBackground.Initialise("sprites/hud/spr_hud_main_0.png", 0, 0, 134, 54, true);
	
	m_HudBackground.setPosition(50, 25);
	m_HudBackground.setScale(2.5, 2.5);

	// -------- Set Up the Animation Sprite Sheet XML -------- //
	pSpriteSheetDef1 = pGameDataManager->GetSpritesheetDef("sprites/hud/spr_hud_face_data.xml");
	pSpriteSheetDef2 = pGameDataManager->GetSpritesheetDef("sprites/hud/spr_icon_health_data.xml");

	// -------- Character Face Animation -------- //
	m_PlayerModel.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef1, "spr_hud_face_biu", 1, false);
	m_PlayerModel.SetCurrentAnimation(1);
	m_PlayerModel.UIObject(true);

	// -------- Health Bar Animation -------- //
	m_HealthBar.AddAnimationFromSpriteSheetDef(1, pSpriteSheetDef2, "spr_icon_health", 1, false);
	m_HealthBar.SetCurrentAnimation(1);
	m_HealthBar.UIObject(true);
}

void HudBase::Update()
{	
	// -------- Gets Current Gamestate Player -------- //
	Player* t_player;
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
	t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());

	// -------- Updates Hud Values -------- //
	UpdateWeapon(t_player->WeaponShotgun);
	UpdateAmmo(t_player->m_pEquippedWeapon->m_CurrentClip);
	UpdateHealth(t_player->PlayerHealth);
	UpdateControls();

	// -------- Dynamic Values -------- //
	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();
	UpdateScore(pAttributeHandler->ScoreString);
	pAttributeHandler->Update();
}

void HudBase::UpdateWeapon(bool Weapon)
{	
	m_WeaponDecal.Initialise("sprites/hud/spr_blitz_0.png", 0, 0, 64, 32, true);
	m_ShotgunDecal.Initialise("sprites/hud/spr_shotgun_1.png", 0, 0, 64, 32, true);

	// -------- Weapon Decal Scale -------- //
	m_WeaponDecal.setScale(1.5, 1.5);
	m_ShotgunDecal.setScale(1.2, 1.2);
	
	// -------- Weapon Decal Update -------- //
	if (Weapon == true)
	{
		m_WeaponDecal.setPosition(1000, 1000);
		m_ShotgunDecal.setPosition(140.0f, 105.0f);
	}
	else
	{
		m_WeaponDecal.setPosition(130.0f, 95.0f);
		m_ShotgunDecal.setPosition(1000, 1000);
	}
}

void HudBase::UpdateAmmo(int Ammo)
{
	// -------- Player Ammo on Screen -------- //
	m_PlayerAmmoText.Initialise("fonts/8-BIT WONDER.TTF", "Ammo " + AmmoString, 15, 235, 110, sf::Color::White, true);

	AmmoString = std::to_string(Ammo);
}

void HudBase::UpdateControls()
{
	// -------- Player Ammo on Screen -------- //
	m_MeleeControlsText.Initialise("fonts/8-BIT WONDER.TTF", "E to Melee", 15, 390, 35, sf::Color::White, true);
	m_ReloadControlsText.Initialise("fonts/8-BIT WONDER.TTF", "R to Reload", 15, 390, 55, sf::Color::White, true);
	m_DashControlsText.Initialise("fonts/8-BIT WONDER.TTF", "SPACE to Dash", 15, 390, 75, sf::Color::White, true);

}

void HudBase::UpdateHealth(int Health)
{
	// -------- Character Face Properties -------- //
	m_PlayerModel.Animate();
	m_PlayerModel.setPosition(60, 80);
	m_PlayerModel.setScale(1.2, 1.2);

	// -------- Health Bar Properties -------- //
	m_HealthBar.Animate();
	m_HealthBar.setPosition(190, 58);
	m_HealthBar.setScale(1.3, 1.3);

	// -------- Hud Update on Player Health -------- //
	if (Health == 3)
	{
		if ((m_PlayerModel.GetCurrentFrame()) == 0) { m_PlayerModel.Pause(); }
		if ((m_HealthBar.GetCurrentFrame()) == 0) { m_HealthBar.Pause(); }
	}
	else if (Health == 2)
	{
		m_PlayerModel.Play();
		m_HealthBar.Play();
		if ((m_PlayerModel.GetCurrentFrame()) == 1) { m_PlayerModel.Pause(); }
		if ((m_HealthBar.GetCurrentFrame()) == 1) { m_HealthBar.Pause(); }
	}
	else if (Health == 1)
	{
		m_PlayerModel.Play();
		m_HealthBar.Play();
		if ((m_PlayerModel.GetCurrentFrame()) == 2) { m_PlayerModel.Pause(); }
		if ((m_HealthBar.GetCurrentFrame()) == 2) { m_HealthBar.Pause(); }
	}
}

void HudBase::UpdateScore(std::string Score)
{
	// -------- Player Score on Screen -------- //
	m_PlayerScoreText.Initialise("fonts/8-BIT WONDER.TTF", "Score " + Score, 35, 80, 170, sf::Color::White, true);
}


void HudBase::GetPosition(int& x, int & y)
{
	m_HudBackground.getPosition().x;
	m_HudBackground.getPosition().y;
}