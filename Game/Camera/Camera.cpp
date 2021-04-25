#include "Camera.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

Camera::Camera()
{
	
}

Camera::~Camera()
{
	RemoveCamera();
}

void Camera::Initialise()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();

	m_View = pWindowManager->GetWindow()->getDefaultView();
}

void Camera::Update()
{
	
	if (m_Active)
	{
		GameStateManager* StateManager = C_SysContext::Get<GameStateManager>();
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		GameState* CurrentState = StateManager->GetCurrentGameState();

		int x;
		int y;

		CurrentState->GetPlayer()->GetPosition(x, y);

		positionX = x;
		positionY = y;

		if(x > 0)
		{
			m_View.setCenter(sf::Vector2f(positionX, positionY));
		}
		
		pWindowManager->GetWindow()->setView(m_View);
	}
}

void Camera::GetPosition(int& x, int& y)
{
	
}

void Camera::SetAsCurrentCamera()
{
	m_Active = true;
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_View);	
}

void Camera::RemoveCamera()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(pWindowManager->GetWindow()->getDefaultView());

	m_Active = false;
}




