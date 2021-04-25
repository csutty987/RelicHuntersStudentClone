#ifndef _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H
#define _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H

#include <SFML\Graphics.hpp>

#include "../../Engine/Input/InputDevice.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Core/MathHelpers.h"

#include <iostream>

class KeyboardAndMouseInputDevice :
	public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	virtual ~KeyboardAndMouseInputDevice();


	virtual void ProcessInputs();

};

#endif

