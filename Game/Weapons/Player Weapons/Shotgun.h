#pragma once
#include "../WeaponBase.h"
#include "../../GameObjects/Bullet/Bullet.h"
#include "../../GameObjects/Bullet/ShotgunShell.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/Audio/AudioManager.h"

class Shotgun :
	public WeaponBase
{
private:

	//bullet spawn pos variables
	int m_BarrelOffsetX;
	int m_BarrelOffsetY;


public:
	Shotgun();
	~Shotgun();

	SpritesheetDef* pSpritesheetDef;
	AudioManager* wAudioManager = C_SysContext::Get<AudioManager>();

	int i = 0;
	virtual void SetReload(int pint);
	virtual void Initialise();
	virtual void Fire();
	virtual void Reload();
	virtual void Update();
};

