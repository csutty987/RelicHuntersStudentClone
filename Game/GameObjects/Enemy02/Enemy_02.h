#pragma once

#include "../../../Application/Project5110/Source/Engine/Renderer/Sprite.h"
#include <SFML/Graphics.hpp>

#include "../Enemy.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Application/Project5110/Source/Game/GameData/GameDataManager.h"
#include "../../../Application/Project5110/Source/Game/GameData/SpritesheetDef.h"
#include "../../../Engine/Input/InputDevice.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Engine/Core/MathHelpers.h"
#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../../../Engine/Audio/AudioManager.h"

class Enemy_02:
	public Enemy, public GameObject, public BoxCollider2D
{
public:
	Enemy_02();
	virtual ~Enemy_02() override;

	void Initialise() override;
	void Update() override;
	void GetPosition(int& x, int & y) override;
	void SetPosition(const int px, const int py);
	void Track(int p_speed);
	bool isNear(float p_length);
	void isFar();
	//void CheckBounds() override;

	int Health;
	void ChangeHealth(int pint);
	bool isDead = false;
	bool hasAttacked = false;
	bool deadComplete = false;
	bool isTooFar = false;

	virtual void OnCollision(Collider2D* pCollider2D);
	
	virtual CollisionType GetCollisionType() override { return CollisionType::E_Enemy; }

	AudioManager* eAudioManager = C_SysContext::Get<AudioManager>();

protected:

	AnimatedSprite m_EAnimatedSprite;
	enum E_AnimationState
	{
		E_IDLE,
		E_WALK,
		E_SPRINT,
	};

	bool check;
	bool lengthCheck;

	int x_init_pos;
	int y_init_pos;
	int l_max;
	int r_max;
	int t_max;
	int b_max;
};

