#ifndef _GAME_STATE_LEVEL_2_H
#define _GAME_STATE_LEVEL_2_H


#include "../../Engine/System/GameState/GameState.h"
#include "../ItemFactory/ItemFactoryManager.h"
#include "../GameObjects/Enemy02/Enemy_02.h"
#include "../GameObjects/Enemy01/Enemy01.h"
#include "../GameObjects/Player/Player.h"
#include "../GameData/SpritesheetDef.h"
#include "../GameObjects/Hud/HudBase.h"
#include "../../Engine/Core/Types.h"
#include "../GameStates/TileMap.h"
#include "../Camera/Camera.h"
#include "../Item/Item.h"
#include "../../Engine/Audio/AudioManager.h"
#include "../../Game/GameObjects/Player/AttributeHandler.h"


class GameStateLevel2 :
	public GameState
{
public:
	GameStateLevel2();
	~GameStateLevel2() override;

	void Initialise() override;
	void Update() override;

	// Player Classes //
	Camera* m_Camera;
	Player* m_Player;
	Bullet* m_Bullet;

	// Enemy Classes //
	Enemy* m_Enemy_02;
	virtual GameObject* GetEnemy() { return m_pEnemies[0]; }

	// HUD and Tilemap //
	HudBase* m_HudBase;
	TileMap* m_Tilemap_Floor_02;
	TileMap* m_Tilemap_Wall_02;

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();

	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();

protected:

	// Player //
	GameObject* GetPlayer() override;
	GameObject* GetBullet();
	Player* DetailedGetPlayer();

	// Item Manager //
	std::vector<Item*> m_Items;
	ItemFactoryManager* m_ItemManager;

	bool musicPlaying = false;

private:
	// Enemy List //
	std::vector<GameObject*> m_pEnemies;
};
#endif