#include "Enemy01Weapon.h"

EnemyWeapon::EnemyWeapon()
{
	
}

EnemyWeapon::~EnemyWeapon()
{
	
}

void EnemyWeapon::Initialise()
{

	m_ClipSize = 1000;
	m_FireRate = 0.5f;
	m_FireTimer = 0.2f;
	m_BarrelOffsetX = 0.0f;
	m_BarrelOffsetY = 0.0f;

	//--------Set Up the Animation Sprite Sheet Info --------

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");
	this->SetScale(1.0f, 1.0f);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_blitz", 24, false);
	m_AnimatedSprite.SetCurrentAnimation(0);
	m_AnimatedSprite.Pause();

	m_BarrelOffsetX = 60;
	m_BarrelOffsetY = -5;

	
}

void EnemyWeapon::Update()
{
	WeaponBase::Update();
}


void EnemyWeapon::Fire()
{
	if (!CanFire())
		return;
	WeaponBase::Fire();

	//generate bullet
	EnemyBullet* enemybullet = new EnemyBullet();
	enemybullet->Initialise();

	//Create a bullet spawn offset
	sf::Vector2f bulletSpawnOffset(m_BarrelOffsetX, m_BarrelOffsetY);

	//Rotate it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	enemybullet->SetPosition(m_AnimatedSprite.getPosition().x + bulletSpawnOffset.x, 
						m_AnimatedSprite.getPosition().y + bulletSpawnOffset.y);

	enemybullet->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	//add it to the current gamestate
	if (pGameState)
		pGameState->AddGameObject(enemybullet);

}

void EnemyWeapon::Reload()
{
}

