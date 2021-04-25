#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../../Application/Project5110/Source/Engine/Renderer/Sprite.h"
#include "../../../Application/Project5110/Source/Engine/Renderer/AnimatedSprite.h"
#include <SFML/Graphics.hpp>
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"


class Item
	:public GameObject
{
public:
	Item();
	virtual ~Item();

	void Initialise() override;
	void Update() override;
	void GetPosition(int& x, int& y) override;



protected:

	AnimatedSprite m_Sprite;
};

