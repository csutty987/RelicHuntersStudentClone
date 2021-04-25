#pragma once
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"

class WeaponBase
{
public:

	WeaponBase();
	virtual ~WeaponBase();

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	//functions
	virtual void Initialise();
	virtual void Fire();
	virtual void Reload();
	virtual void Update();

	
	bool CanFire();
	void SetPosition(int posx, int posy);
	void SetScale(float scaleX, float scaleY);
	void SetRotation(float angle);
	void SetReload(int pint);

	AnimatedSprite m_AnimatedSprite;

	//weapon variables
	int i = 0;
	int m_ClipSize;
	float m_FireRate;
	float m_FireTimer;
	int m_CurrentClip;
};

