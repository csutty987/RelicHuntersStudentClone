#ifndef _GAME_STATE_MAIN_MENU_H
#define _GAME_STATE_MAIN_MENU_H

#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../GameObjects/Menu/MenuItems.h"
#include "../GameObjects/Menu/MenuBase.h"
#include "../GameObjects/Player/Player.h"
#include "../Camera/Camera.h"


class GameStateMainMenu :
	public GameState
{
public:
	GameStateMainMenu();
	~GameStateMainMenu();

	void Initialise();
	void Update();

	// -------- Pointers -------- //
	Player* m_Player;
	GameObject* m_Bullet;
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();

	// -------- Menu Base -------- //
	MenuBase* m_MenuBase;
	MenuItems* m_MenuItems;

protected:

	// -------- Player -------- //
	GameObject* GetPlayer();
	GameObject* GetBullet();
	Player* DetailedGetPlayer();
	
};

#endif