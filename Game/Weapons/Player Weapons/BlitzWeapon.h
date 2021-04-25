#pragma once
#include "../WeaponBase.h"
#include "../../GameObjects/Bullet/Bullet.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/Audio/AudioManager.h"

class BlitzWeapon :
	public WeaponBase
{
private:
	
	//bullet spawn pos variables
	int m_BarrelOffsetX;
	int m_BarrelOffsetY;

public:
	BlitzWeapon();
	~BlitzWeapon();
	
	int ammoref;
	SpritesheetDef* pSpritesheetDef;
	AudioManager* wAudioManager = C_SysContext::Get<AudioManager>();
	
	float m_WeaponOffsetX = 0.0f;
	float m_WeaponOffsetY = 0.0f;
	int i = 0;

	virtual void SetReload(int pint);
	virtual void Initialise();
	virtual void Fire();
	virtual void Reload();
	virtual void Update();
};

