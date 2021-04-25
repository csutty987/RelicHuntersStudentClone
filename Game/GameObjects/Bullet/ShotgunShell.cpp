#include "ShotgunShell.h"
#include <iostream>


ShotgunShell::ShotgunShell()
{

}

ShotgunShell::~ShotgunShell()
{

}

void ShotgunShell::Initialise()
{
	// -------- Set Up the Animation Sprite Sheet Info --------
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_bullet", 24);

	m_AnimatedSprite.SetCurrentAnimation(0);

	m_Velocity = 2400.0f;
	m_Lifetime = 0.15f;
	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

}

void ShotgunShell::Update()
{
	m_AnimatedSprite.Animate();

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	//don't move until we are past the muzzle flash frame
	if (m_AnimatedSprite.GetCurrentFrame() == 0)
		return;

	//grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//create a forward vector
	sf::Vector2f movement(1.0f, 0.0f);

	//modify magnitude based on velocity
	movement *= (m_Velocity * pFrameTimer->DeltaTime());

	//rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	movement = transform.transformPoint(movement);

	//transform the bullet position
	m_AnimatedSprite.move(movement);

	m_Lifetime -= pFrameTimer->DeltaTime();
	if (m_Lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);

	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

}

void ShotgunShell::GetPosition(int& x, int& y)
{
	m_AnimatedSprite.getPosition().x;
	m_AnimatedSprite.getPosition().y;
}

void ShotgunShell::OnCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	if (pCollider2D->GetCollisionType() == CollisionType::E_Enemy)
	{

		pCurrentGameState->RemoveGameObject(this);
	}
}

void ShotgunShell::SetPosition(int x, int y)
{
	m_AnimatedSprite.setPosition(x, y);

}

void ShotgunShell::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}

void ShotgunShell::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}