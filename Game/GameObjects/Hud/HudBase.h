#pragma once
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../GameObjects/Player/AttributeHandler.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"
#include "../../GameObjects/Player/Player.h"
#include "../../../Engine/UI/Text.h"

class HudBase :
	public GameObject
{
public:
	HudBase();
	~HudBase();

	void Initialise();
	void Update();

	void GetPosition(int& x, int & y) override;

	// Update Hud Functions  //
	void UpdateHealth(int Health);
	void UpdateWeapon(bool Weapon);
	void UpdateScore(std::string Score);
	void UpdateAmmo(int Ammo);
	void UpdateControls();

	bool UIObjectMain;

	std::string ScoreString;
	std::string AmmoString;

	// Sprite Sheet Functionality //
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef1;
	SpritesheetDef* pSpriteSheetDef2;

	// Animated Sprites //
	AnimatedSprite m_PlayerModel;
	AnimatedSprite m_HealthBar;
	Text m_PlayerScoreText;
	Text m_PlayerAmmoText;
	Text m_MeleeControlsText;
	Text m_ReloadControlsText;
	Text m_DashControlsText;

	// Static Sprites //
	Sprite m_HudBackground;
	Sprite m_WeaponDecal;
	Sprite m_ShotgunDecal;

};
