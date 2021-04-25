#include "BlitzWeapon.h"


BlitzWeapon::BlitzWeapon()
{
	
}

BlitzWeapon::~BlitzWeapon()
{
	
}

void BlitzWeapon::Initialise()
{
	m_ClipSize = 10;
	m_FireRate = 1.2f;
	m_FireTimer = 0.5f;
	m_BarrelOffsetX = 0.0f;
	m_BarrelOffsetY = 0.0f;
	m_CurrentClip = m_ClipSize;
	ammoref = m_CurrentClip;
	
	// -------- Set Up the Animation Sprite Sheet Info --------
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");
	
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_blitz", 15, false);

	m_AnimatedSprite.SetCurrentAnimation(0);
	
	m_AnimatedSprite.Pause();
}

void BlitzWeapon::Fire()
{
	if (!CanFire())
		return;

	WeaponBase::Fire();

	m_AnimatedSprite.Play();

	wAudioManager->PlaySoundFX("sounds/sfx_rifle1.wav", false);

	//generate bullet
	Bullet* bullet = new Bullet();

	bullet->Initialise();

	//create bullet spawn offset
	sf::Vector2f bulletSpawnOffset(m_BarrelOffsetX, m_BarrelOffsetY);

	//rotate it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	bullet->SetPosition(m_AnimatedSprite.getPosition().x + bulletSpawnOffset.x, m_AnimatedSprite.getPosition().y + bulletSpawnOffset.y);
	bullet->SetRotation(m_AnimatedSprite.getRotation());
	bullet->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	//add it to the current gamestate
	if (pGameState)
		pGameState->AddGameObject(bullet);

	m_CurrentClip -= 1;	
}

void BlitzWeapon::Reload()
{
	m_CurrentClip = m_ClipSize;
}

void BlitzWeapon::Update()
{
	WeaponBase::Update();
}

void BlitzWeapon::SetReload(int pint)
{
	WeaponBase::SetReload(pint);
}




