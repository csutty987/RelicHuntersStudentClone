#pragma once
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"

#include "../../../Engine/Physics/BoxCollider2D.h"
class EnemyBullet :
	public GameObject, BoxCollider2D
{
public:
	EnemyBullet();
	~EnemyBullet();

private:
	float m_Velocity;
	float m_Lifetime;
	
	AnimatedSprite  m_animated_sprite_;

public:
	void virtual Initialise() override;
	void virtual  Update() override;
	virtual void GetPosition(int& x, int& y) override;
	virtual void OnCollision(Collider2D* pCollider2D);
	
	virtual CollisionType GetCollisionType() override { return CollisionType::E_EnemyBullet; }
	//void virtual OnCollision(Collider2D* pCollider2D) override;
	void SetPosition(int x, int y);
	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);
	
};

