#pragma once
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/FrameTimer.h"
#include "../../GameData/GameDataManager.h"
#include "../../../Engine/System/GameState/GameState.h"

class Bullet :
	public GameObject, BoxCollider2D
{

private:
	float m_Velocity;
	float m_Lifetime;

	AnimatedSprite m_AnimatedSprite;
	
public:
	Bullet();
	~Bullet();
	
	SpritesheetDef* pSpritesheetDef;
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);
	virtual void OnCollision(Collider2D* pCollider2D);
	virtual CollisionType GetCollisionType() override { return CollisionType::E_PlayerBullet; }
	
	void SetPosition(int x, int y);
	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);
};

