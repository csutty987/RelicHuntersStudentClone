#pragma once
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../../Game/GameData/GameDataManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Engine/Input/InputDevice.h"
#include "../../Weapons/WeaponBase.h"
#include "../../Weapons/Player Weapons/BlitzWeapon.h"
#include "../../Weapons/Player Weapons/Shotgun.h"
#include "../../../Engine/Utils/Utils.h"
#include "../../../Engine/Core/MathHelpers.h"
#include "../../../Engine/Renderer/Sprite.h"
#include "../../GameObjects/Hud/HudBase.h"
#include "../../GameObjects/Player/AttributeHandler.h"
#include "../../../Engine/Audio/AudioManager.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Player :
	public GameObject, public BoxCollider2D
{
public:
	Player();
	~Player();
	
	void Initialise();
	void Update();
	void GetPosition(int& x, int & y) override;

	float m_WeaponOffsetX = 0.0f;
	float m_WeaponOffsetY = 0.0f;

	void OnHit();

	virtual void OnCollision(Collider2D* pCollider2D);

	void ChangeHealth(int pint);

	void SetSurroundingTileNum(int uptilenum, int downtilenum, int lefttilenum, int righttilenum);
	void SetPlayerTileNum(int tilenum);
	int p_tilenum;
	int up_tilenum;
	int down_tilenum;
	int left_tilenum;
	int right_tilenum;

	bool stateReload = false;

	bool isDead;
	bool WeaponShotgun;

	int PlayerHealth;
	int EnemiesHit;
	int PlayerScore;
	float DashTime = 1.0f;

	float PlayerSpeed;

	void ChangeScore(int pscore);
	void ChangeSpeed(float pfloat);
	void ChangeEnemiesHit(int hitCount);

	void setSpeed(float pfloat);
	
	virtual CollisionType GetCollisionType() override { return CollisionType::E_Player; }

	//Pointers
	AttributeHandler* pAttributeHandler = C_SysContext::Get<AttributeHandler>();
	WeaponBase* m_pEquippedWeapon;
	WeaponBase* m_pWeapon;
	WeaponBase* m_pShotgun;
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();

	//Walk
	sf::SoundBuffer walkBuffer;
	sf::Sound Walk;

	//Melee
	sf::SoundBuffer meleeBuffer;
	sf::Sound melee;

	//Dash
	sf::SoundBuffer dashBuffer;
	sf::Sound dash;

	//Shotgun Reload
	sf::SoundBuffer sReloadBuffer;;
	sf::Sound sReload;
	//Rifle Reload
	sf::SoundBuffer rReloadBuffer;;
	sf::Sound rReload;

protected:
	
	// -------- Pointers --------
//private:
	AnimatedSprite m_AnimatedSprite;

	void StillAlive();
	void PlayerMovement();

	void WeaponManager();
	void UpdateWeapon();

	void Fire();
	void Reload();

	// -------- Enums --------
	enum E_AnimationState
	{
		E_AnimationStateIdle,

		E_AnimationStateSprint,

		E_AnimationStateWalk,

		E_AnimationStateMelee,

		E_AnimationStateHit,

		E_AnimationStateDash,

		E_AnimationStateDeath
	};

	bool isMoving;
	bool weaponSwitch = false;
	bool musicPlaying = false;

	int i = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
};

