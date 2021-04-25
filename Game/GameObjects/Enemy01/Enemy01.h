#pragma once
#include "../Enemy.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Game/GameData/GameDataManager.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Engine/Input/InputDevice.h"
#include "../../../Engine/Renderer/FrameTimer.h"
#include "../../../Engine/Utils/Utils.h"
#include "../../Weapons/WeaponBase.h"
#include "../../Weapons/Enemy Weapons/Enemy01Weapon.h"
#include "../../GameObjects/Player/Player.h"
#include "../../../Engine/Audio/AudioManager.h"

class Enemy01 :
	public Enemy, public GameObject, public BoxCollider2D
{
public:
//--------Constructor and destructor//--------
	Enemy01();
	~Enemy01() override;

//----------Inherited from Base class----------
	void Initialise();
	void Update();
	void GetPosition(int& x, int & y) override;
	void SetPosition(int x, int y) { this->m_animated_sprite_.setPosition(x, y); }
	void SetDirection(bool faceRight)
	{
		if (faceRight)
		{
			m_faceDir = 1.0f;
		}
		else
		{
			m_faceDir = -1.0f;
		}

	}

	virtual void OnCollision(Collider2D* pCollider2D);

	void Fire();
	void Reload();
	//virtual void SetPosition(const int px, const int py);

	float m_WeaponOffsetX = 0.0f;
	float m_WeaponOffsetY = 0.0f;
	float m_faceDir = 0.0f;


	int Health;

	bool hasAttacked;
	bool isDead;
	bool deadComplete = false;

	void ChangeHealth(int pint);

	virtual CollisionType GetCollisionType() override { return CollisionType::E_Enemy; }
	
//------------------Pointers--------------------

	
	
	//int animationId;
	//const char* animationName;
	//int fps;
	//bool loop;
protected:
	AnimatedSprite m_animated_sprite_;

	Player* m_player;
	
	EnemyWeapon*	m_pWeapon;

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();
	AudioManager* eAudioManager = C_SysContext::Get<AudioManager>();

enum E_AnimationState
{
	E_AnimationStateIdle,

	E_AnimationStateSprint,

	E_AnimationStateWalk,

	//E_AnimationState_TeleportIn
};

int x_init_pos;
int y_init_pos;
int l_max;
int r_max;
int t_max;
int b_max;
	
};

