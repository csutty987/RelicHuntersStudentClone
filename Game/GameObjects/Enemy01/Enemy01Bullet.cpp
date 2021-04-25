#include "Enemy01Bullet.h"

#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/SpritesheetDef.h"
#include "../../../Engine/Renderer/FrameTimer.h"

#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include <iostream>


EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Initialise()
{

	// -------- Set Up the Animation Sprite Sheet Info --------
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");

	m_animated_sprite_.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_bullet", 24, false);
	m_animated_sprite_.SetCurrentAnimation(0);

	m_Velocity = 600.0f;
	m_Lifetime = 0.75f;

	m_CollisionRect = m_animated_sprite_.getGlobalBounds();
}

void EnemyBullet::Update()
{
	m_animated_sprite_.Animate();

	m_CollisionRect = m_animated_sprite_.getGlobalBounds();

	//don't move until we are past the muzzle flash frame
	if (m_animated_sprite_.GetCurrentFrame() == 0)
		return;

	//grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//create a forward vector
	sf::Vector2f movement(1.0f, 0.0f);

	//modify magnitude based on velocity
	movement *= (m_Velocity * pFrameTimer->DeltaTime());

	//rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_animated_sprite_.getRotation());
	transform.scale(m_animated_sprite_.getScale());
	movement = transform.transformPoint(movement);

	//transform the bullet position
	m_animated_sprite_.move(movement);

	m_Lifetime -= pFrameTimer->DeltaTime();
	if (m_Lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);

	}

}

void EnemyBullet::GetPosition(int& x, int& y)
{
	m_animated_sprite_.getPosition().x;
	m_animated_sprite_.getPosition().y;
}

void EnemyBullet::OnCollision(Collider2D * pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	if (pCollider2D->GetCollisionType() == CollisionType::E_Player)
	{

		pCurrentGameState->RemoveGameObject(this);
	}
}

void EnemyBullet::SetPosition(int x, int y)
{
	m_animated_sprite_.setPosition(x, y);
}

void EnemyBullet::SetRotation(float angle)
{
	m_animated_sprite_.setRotation(angle);
}

void EnemyBullet::SetScale(float scaleX, float scaleY)
{
	m_animated_sprite_.setScale(scaleX, scaleY);
}

