#pragma once
#include <SFML/Graphics/View.hpp>
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/WindowManager.h"


class Camera:
	public GameObject
{
public:
	
	Camera();
	~Camera();
	
	void Initialise() override;
	void Update() override;
	
	void GetPosition(int& x, int& y) override;

	void SetAsCurrentCamera();
	void RemoveCamera();

private:

	sf::View m_View;
	bool m_Active;

	float positionX;
	float positionY;

	
};

