#include "WeaponBase.h"

WeaponBase::WeaponBase()
{
	m_ClipSize = 6;
	m_CurrentClip = m_ClipSize;
	m_FireRate = 0.8f;
	m_FireTimer = 1.0f;
}

WeaponBase::~WeaponBase()
{
	
}

void WeaponBase::Initialise()
{
	
}

void WeaponBase::Fire()
{
	if (m_FireRate > 0.0f)
	{
		m_FireTimer = 1.0f / m_FireRate;
	}
}

void WeaponBase::Reload()
{
	
}

void WeaponBase::Update()
{
	//handle animation updates
	m_AnimatedSprite.Animate();

	if (m_AnimatedSprite.AnimationFinished())
	{
		m_AnimatedSprite.SetCurrentAnimation(0);
		m_AnimatedSprite.Pause();
	}

	if (m_FireTimer >= 0.0f)
	{
		FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
		m_FireTimer -= pFrameTimer->DeltaTime();
	}
	
}

bool WeaponBase::CanFire()
{
	if (m_CurrentClip > 0)
	{
		return m_FireTimer <= 0.0f;
	}
	return false;
}

void WeaponBase::SetPosition(int posx, int posy)
{
	m_AnimatedSprite.setPosition(posx, posy);
}

void WeaponBase::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}

void WeaponBase::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}

void WeaponBase::SetReload(int pint)
{
	i = pint;
}



