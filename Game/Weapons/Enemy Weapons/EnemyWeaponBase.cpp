#include "EnemyWeaponBase.h"



WeaponBase::WeaponBase()
{
}


WeaponBase::~WeaponBase()
= default;

void WeaponBase::initialise()
{
}

void WeaponBase::Fire()
{
	if(m_FireRate > 0.0f)
	{
		m_FireTimer = 1.0f / m_FireRate;
	}
}

void WeaponBase::Reload()
{
}

void WeaponBase::Update()
{
	m_animated_sprite_.Animate();
	
	if(m_animated_sprite_.AnimationFinished())
	{
		m_animated_sprite_.SetCurrentAnimation(0);
		m_animated_sprite_.Pause();
	}

	if (m_FireTimer >= 0.0f)
	{
		FrameTimer* p_frame_timer = C_SysContext::Get<FrameTimer>();
		m_FireTimer -= p_frame_timer->DeltaTime();
	}

}

bool WeaponBase::CanFire()
{
	if (m_Ammo > 0)
	{
		return m_FireTimer <= 0.0f;
	
	}
	return false;
}

void WeaponBase::SetPosition(int posx, int posy)
{
	m_animated_sprite_.setPosition(posx, posy);
}

void WeaponBase::SetScale(float scaleX, float ScaleY)
{
	m_animated_sprite_.setScale(scaleX, ScaleY);

}

void WeaponBase::SetRotation(float angle)
{
	m_animated_sprite_.setRotation(angle);
}
