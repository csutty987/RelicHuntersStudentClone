#ifndef _BOX_COLLIDER_2D
#define _BOX_COLLIDER_2D

#include "Collider2D.h"
#include <SFML/Graphics.hpp>
#include "../../Game/GameStates/TileMap.h"

class BoxCollider2D : public Collider2D
{
public:
	BoxCollider2D();
	virtual ~BoxCollider2D();

	virtual bool CollidesWith(Collider2D* pCollider2D);
	virtual bool CollidesWith(BoxCollider2D* pBoxCollider2D);
	virtual bool CollidesWith(CircleCollider2D* pCircleCollider2D);

	bool CollidesWith(TileMap* pCollider2D) override;

	/*enum CollisionType
	{
		E_Player,

		E_Enemy,

		E_PlayerBullet,

		E_EnemyBullet,

		E_Wall,

		E_Floor,

		E_All,

		E_Pickup

	};

	virtual CollisionType GetCollisionType() = 0 { return CollisionType::E_All; };*/

//protected:

	sf::FloatRect m_CollisionRect;
};

#endif

