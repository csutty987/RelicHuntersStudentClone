#include "Shotgun.h"


Shotgun::Shotgun()
{

}

Shotgun::~Shotgun()
{

}

void Shotgun::Initialise()
{
	float m_WeaponOffsetX = 0.0f;
	float m_WeaponOffsetY = 0.0f;
	int m_ClipSize = 6;
	float m_FireRate = 0.5f;
	float m_FireTimer = 0.5;
	m_CurrentClip = m_ClipSize;


	// -------- Set Up the Animation Sprite Sheet Info --------
	pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_shotgun/spr_shotgun.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_shotgun", 15, false);

	m_AnimatedSprite.SetCurrentAnimation(0);

	m_AnimatedSprite.Pause();

}

void Shotgun::Fire()
{
	if (!CanFire())
		return;
	WeaponBase::Fire();

	m_AnimatedSprite.Play();

	wAudioManager->PlaySoundFX("sounds/sfx_shotgun.wav", false);

	int rotateint = 0;
	//generate bullet
	for (int i = 1; i < 5; i++)
	{
		ShotgunShell* shotgunshell = new ShotgunShell();

		shotgunshell->Initialise();

		//create bullet spawn offset
		sf::Vector2f bulletSpawnOffset(m_BarrelOffsetX, m_BarrelOffsetY);

		//rotate it to face the correct direction
		sf::Transform transform;
		transform.rotate(m_AnimatedSprite.getRotation());
		transform.scale(m_AnimatedSprite.getScale());
		bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

		shotgunshell->SetPosition(m_AnimatedSprite.getPosition().x + bulletSpawnOffset.x, m_AnimatedSprite.getPosition().y + bulletSpawnOffset.y);
		shotgunshell->SetRotation((m_AnimatedSprite.getRotation() + rotateint));
		shotgunshell->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);
		rotateint += 10;

		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();

		//add it to the current gamestate
		if (pGameState)
			pGameState->AddGameObject(shotgunshell);
	}



	m_CurrentClip -= 1;
}

void Shotgun::Reload()
{
	m_CurrentClip = m_ClipSize;
}

void Shotgun::Update()
{
	WeaponBase::Update();
}

void Shotgun::SetReload(int pint)
{
	WeaponBase::SetReload(pint);
}




