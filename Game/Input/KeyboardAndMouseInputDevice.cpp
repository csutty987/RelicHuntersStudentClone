#include "KeyboardAndMouseInputDevice.h"

KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{

}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{

}

void KeyboardAndMouseInputDevice::ProcessInputs()
{

	m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
	m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::D));

	m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? 1.0f : 0.0f);

	m_DigitalInputs[E_DigitalInput_Start].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	m_DigitalInputs[E_DigitalInput_LeftShoulder].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1));
	m_DigitalInputs[E_DigitalInput_Y].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2));
	m_DigitalInputs[E_DigitalInput_X].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::R));
	m_DigitalInputs[E_DigitalInput_B].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::E));
	m_DigitalInputs[E_DigitalInput_A].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
	m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));

	//  WIP Mouse Tracking

	/*m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
	m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);
*/
	// ----------- Get Mouse Position relative to window/world, then convert the vector into a value between -1 and 1 for both X and Y values to track the mouse Pos to Analogue Sticks.

	GameStateManager*  pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	GameObject* pPlayerObject = pGameState->GetPlayer();

	int playerPosX = 0;
	int playerPosY = 0;

	pPlayerObject->GetPosition(playerPosX, playerPosY);

	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();

	const sf::View view = pWindow->getView();

	//get mouse position relative to window
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);

	//get the mouse world position
	sf::Vector2f offsetPos((view.getCenter().x - (view.getSize().x * 0.5f)), view.getCenter().y - (view.getSize().y * 0.5f));
	sf::Vector2f mouseWorldPos(mousePosition.x + offsetPos.x, mousePosition.y + offsetPos.y);

	sf::Vector2f distance((float)mouseWorldPos.x - (float)playerPosX, (float)mouseWorldPos.y - (float)playerPosY);
	//sf::Vector2f distance(((float)mouseWorldPos.x + 0.0f), (float)mouseWorldPos.y);

	distance = MathHelpers::Normalise(distance);

	m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(distance.x);
	m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(distance.y);


	m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? 1.0f : 0.0f);
	// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

}