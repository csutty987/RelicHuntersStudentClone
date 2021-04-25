#pragma once
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../GameData/GameDataManager.h"

class MenuBase :
	public GameObject
{
public:
	MenuBase();
	~MenuBase();

	void Initialise();
	void Update();

	void GetPosition(int& x, int & y) override;

	// Manager Pointer //
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	// SpriteSheet Defs //
	SpritesheetDef* pSpriteSheetDef1;
	SpritesheetDef* pSpriteSheetDef2;

	// Animated Sprites //
	AnimatedSprite m_MenuLogo;
	AnimatedSprite m_MenuBackground;

};