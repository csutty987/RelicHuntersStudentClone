#pragma once
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../GameObjects/AnimatedSpriteGameObject.h"
#include "../../../Engine/Renderer/FrameTimer.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../GameData/GameDataManager.h"

class WeaponBase 
{
//-------------Constructer and Base class Destructure-----------
public: 
	WeaponBase();
	virtual  ~WeaponBase();

//-----------------------------Protected variables--------------------
protected:

	int m_Ammo;
	float m_FireRate;
	float m_FireTimer;
	AnimatedSprite  m_animated_sprite_;



//--------------------------Functions-------------------------------
public:
	virtual void initialise();
	virtual void Fire();
	virtual void Reload();
	virtual void Update();

	bool CanFire();
	
	void SetPosition(int posx, int posy);
	void SetScale(float scaleX, float ScaleY);
	void SetRotation(float angle);

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef;

	

	
	
};

