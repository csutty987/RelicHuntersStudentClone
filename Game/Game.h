#ifndef _GAME_H
#define _GAME_H

#include "../Engine/Renderer/RenderManager.h"
#include "../Engine/System/Assets/AssetManager.h"
#include "../Engine/Renderer/FrameTimer.h"
#include "../Engine/System/GameState/GameStateManager.h"
#include "../Engine/Audio/AudioManager.h"
#include "../Engine/Input/InputManager.h"
#include "../Engine/Renderer/WindowManager.h"
#include "GameData/GameDataManager.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateLevel1.h"
#include "GameStates/GameStateLevel2.h"
#include "GameStates/GameStateEnd.h"
#include "Input/KeyboardAndMouseInputDevice.h"
#include "ItemFactory/ItemFactoryManager.h"
#include "GameObjects/Player/AttributeHandler.h"

class InputDevice;

class Game
{
public:

	Game();
	~Game();

	void Initialise();
	void Run();
	void LoadGameStates();


private:

	bool m_bExit;

	// -------- Game Managers -------- //
	GameDataManager m_GameDataManager;
	WindowManager m_WindowManager;	
	FrameTimer m_FrameTimer;
	RenderManager m_RenderManager;
	AssetManager m_AssetManager;
	GameStateManager m_GameStateManager;
	AudioManager m_AudioManager;
	InputManager m_InputManager;
	InputDevice* m_pInputDevice;
	AttributeHandler m_AttributeHandler;

	// -------- Game States -------- //
	GameStateMainMenu* m_GameStateMenu;
	GameStateLevel1* m_GameStateLevel1;
	GameStateLevel2* m_GameStateLevel2;
	GameStateEnd* m_GameStateEnd;
	GameStateMainMenu* m_GameStateMenu2;

	// -------- Item Factory -------- //
	ItemFactoryManager m_ItemFactoryManager;
	ItemFactory* m_pItemFactory;
};

#endif
