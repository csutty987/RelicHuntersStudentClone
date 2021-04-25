#ifndef _GAME_STATE_END_H
#define _GAME_STATE_END_H

#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../GameObjects/Menu/MenuBase.h"
#include "../GameObjects/Player/Player.h"
#include "../../Engine/UI/Text.h"
#include "../Camera/Camera.h"
#include <string>
#include "../../Engine/Audio/AudioManager.h"

class GameStateEnd :
	public GameState
{
public:
	GameStateEnd();
	~GameStateEnd();

	void Initialise();
	void Update();

	void UpdatePlayerScore(std::string Score);

	std::string PlayerScoreFinal;

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();
	AudioManager* gAudioManager = C_SysContext::Get<AudioManager>();

	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	SpritesheetDef* pSpriteSheetDef1;
	SpritesheetDef* pSpriteSheetDef2;
	
	Player* m_Player;
	GameObject* m_Bullet;

	Text m_MainText;
	Text m_PlayerScore;
	Text m_YouWinText;

	MenuBase* m_MenuBase;

	AnimatedSprite m_ReturnButton;
	AnimatedSprite m_ExitButton;

	int i = 0;

protected:

	GameObject* GetPlayer();
	GameObject* GetBullet();
	Player* DetailedGetPlayer();

};

#endif