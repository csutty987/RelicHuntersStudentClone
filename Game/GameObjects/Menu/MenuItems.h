#pragma once
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"
#include "../../GameData/GameDataManager.h"

class AttributeHandler;

class MenuItems :
	public GameObject
{
public:
	MenuItems();
	~MenuItems();

	void Initialise();
	void Update();

	void GetPosition(int& x, int & y) override;

	// Manager Pointers //
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();

	// SpriteSheet Defs //
	SpritesheetDef* pSpriteSheetDef1;
	SpritesheetDef* pSpriteSheetDef2;

	// Animated Sprites //
	AnimatedSprite m_StartButton;
	AnimatedSprite m_ExitButton;

	// Static Sprites //
	Sprite m_Controls;
};
