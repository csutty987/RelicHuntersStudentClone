#include "Game.h"

#include <windows.h>
#include <iostream>

#include "../Engine/Utils/Utils.h"
#include "../Engine/System/Context/SysContextProvider.h"
#include "../Engine/Input/InputDevice.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

Game::Game()
	:m_bExit(false)
	,m_pInputDevice(NULL)
{
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pInputDevice);
}

void Game::Initialise()
{
	C_SysContext::Initialise();

	//setup the game data manager
	m_GameDataManager.Initialise();
	C_SysContext::Set<GameDataManager>(&m_GameDataManager);

	//setup the frame timer
	C_SysContext::Set<FrameTimer>(&m_FrameTimer);

	//setup the window manager
	C_SysContext::Set<WindowManager>(&m_WindowManager);

	//setup the asset manager
	C_SysContext::Set<AssetManager>(&m_AssetManager);

	//setup the renderer
	m_RenderManager.Initialise(WINDOW_WIDTH, WINDOW_HEIGHT, "5110Comp - Group 7 - Software Engineering");
	C_SysContext::Set<RenderManager>(&m_RenderManager);

	//setup the audio manager
	C_SysContext::Set<AudioManager>(&m_AudioManager);

	//setup the input manager
	m_InputManager.Initialise();
	m_pInputDevice = new KeyboardAndMouseInputDevice();
	m_InputManager.SetInputDevice(m_pInputDevice);
	C_SysContext::Set<InputManager>(&m_InputManager);

	//setup the game state manager
	m_GameStateManager.Initialise();
	C_SysContext::Set<GameStateManager>(&m_GameStateManager);

	//Setup the Attribute Handler
	m_AttributeHandler.Initialise();
	C_SysContext::Set<AttributeHandler>(&m_AttributeHandler);

	//setup the item factory manager
	m_ItemFactoryManager.Initialise();
	m_pItemFactory = new ItemFactoryImplementation();
	m_ItemFactoryManager.SetFactory(m_pItemFactory);
	C_SysContext::Set<ItemFactoryManager>(&m_ItemFactoryManager);
	
	//Queue oru GameStates
	LoadGameStates();
}

void Game::Run()
{
	m_FrameTimer.Initialise();

	while (!m_bExit)
	{
		//start of game frame
		m_FrameTimer.StartFrame();

		//update the game state
		m_GameStateManager.Update();

		//update Player Input First
		m_InputManager.Update();

		//update the audio manager
		m_AudioManager.Update();

		//render
		m_RenderManager.Render();

		//Game Loop
		if (m_AttributeHandler.GameRestart == true)
		{
			LoadGameStates();
			m_GameStateManager.QueuePop();
		}

		//end of game frame
		m_FrameTimer.EndFrame();	
	}
}

void Game::LoadGameStates()
{

	m_GameStateMenu2 = new GameStateMainMenu();
	m_GameStateManager.QueueGameState(m_GameStateMenu2);

	m_GameStateEnd = new GameStateEnd();
	m_GameStateManager.QueueGameState(m_GameStateEnd);

	m_GameStateLevel2 = new GameStateLevel2();
	m_GameStateManager.QueueGameState(m_GameStateLevel2);

	m_GameStateLevel1 = new GameStateLevel1();
	m_GameStateManager.QueueGameState(m_GameStateLevel1);

	m_GameStateMenu = new GameStateMainMenu();
	m_GameStateManager.QueueGameState(m_GameStateMenu);
}

