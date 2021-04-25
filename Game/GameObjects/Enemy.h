#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"

class Enemy
	: public GameObject
{
public:
	//Constucor and Destructor
	Enemy();
	Enemy(int px, int py, int plmax, int prmax, int ptmax, int pbmax);
	virtual ~Enemy();

	//Base class functions
	void virtual Initialise();
	void virtual Update();
	void virtual GetPosition(int& x, int & y);
	void virtual CheckBounds();

protected:
	AnimatedSprite m_animated_sprite_;
	int x_init_pos;
	int y_init_pos;
	int l_max;
	int r_max;
	int t_max;
	int b_max;
};

