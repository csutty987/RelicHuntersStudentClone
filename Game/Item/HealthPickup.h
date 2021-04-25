#pragma once
#include "Item.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Audio/AudioManager.h"

class HealthPickup :
	public Item, BoxCollider2D
{
public:
	HealthPickup(int px, int py);
	~HealthPickup() override;

	void Initialise() override;

	void Update() override;

	void GetPosition(int& x, int& y) override;
	void SetPosition(int& x, int& y);

	bool SFXPlayed = false;

	void OnCollision(Collider2D* pCollider2D) override;
	virtual CollisionType GetCollisionType() override { return CollisionType::E_HP; }
	std::vector<sf::IntRect> m_Frames;
	std::vector<sf::Vector2f> m_Origins;
	

protected:

	AnimatedSprite m_Sprite;
	int x_pos;
	int y_pos;
};

