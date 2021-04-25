#pragma once
#include "../../Weapons/WeaponBase.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../GameObjects/Bullet/Bullet.h"
#include "../../GameObjects/Enemy01/Enemy01Bullet.h"
class EnemyWeapon :
	public WeaponBase
{
private:
	int m_BarrelOffsetX;
	int m_BarrelOffsetY;

	

public:
	EnemyWeapon();
	~EnemyWeapon();
	void Initialise() override;
	virtual void Fire() override;
	virtual void Reload() override;
	virtual void Update() override;

	
};

