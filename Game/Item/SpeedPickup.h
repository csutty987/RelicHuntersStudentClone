#pragma once
#include "Item.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Game/GameObjects/Player/Player.h"
#include "../../Engine/Audio/AudioManager.h"

class SpeedPickup :
	public Item, BoxCollider2D
{
public:
	SpeedPickup(int px, int py);
	~SpeedPickup() override;

	void Initialise() override;

	void Update() override;

	void GetPosition(int& x, int& y) override;
	void SetPosition(int& x, int& y);

	void OnCollision(Collider2D* pCollider2D) override;

	bool SFXPlayed = false;

	virtual CollisionType GetCollisionType() override { return CollisionType::E_SP; }

protected:

	AnimatedSprite m_Sprite;
	int x_pos;
	int y_pos;
	std::vector<sf::IntRect> m_Frames;
	std::vector<sf::Vector2f> m_Origins;
};

