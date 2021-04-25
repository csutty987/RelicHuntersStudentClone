#include "Enemy01.h"

#include <iostream>


Enemy01::Enemy01()

	:Health(2)
	,isDead(false)
	,hasAttacked(false)
{
}

Enemy01::~Enemy01()
{
	SAFE_DELETE_PTR(m_pWeapon);
}

void Enemy01::Initialise()
{
	const int framerate = 10;


	GameDataManager* p_game_data_manager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* p_spritesheet_def;

	p_spritesheet_def = p_game_data_manager->GetSpritesheetDef("sprites/characters/spr_enemy.xml");


	// -------- --------------Populate Animation State ------------------------------------------------

	m_animated_sprite_.AddAnimationFromSpriteSheetDef(E_AnimationStateIdle, p_spritesheet_def, "spr_enemy", 15);
	m_animated_sprite_.AddAnimationFromSpriteSheetDef(E_AnimationStateWalk, p_spritesheet_def, "spr_enemy_weakspot", 15);
	m_animated_sprite_.AddAnimationFromSpriteSheetDef(E_AnimationStateSprint, p_spritesheet_def, "spr_enemy_hit", 15);
	//m_animated_sprite_.SetCurrentAnimation(E_AnimationState_TeleportIn);

	m_animated_sprite_.setScale(1.0f * m_faceDir, 1.0f);

	m_animated_sprite_.setPosition(x_init_pos, y_init_pos); //give an initial position

	m_WeaponOffsetX = 0;
	m_WeaponOffsetY = 20;
	m_pWeapon = new EnemyWeapon();
	m_pWeapon->Initialise();

	m_CollisionRect = m_animated_sprite_.getGlobalBounds();
	m_animated_sprite_.SetCurrentAnimation(E_AnimationStateIdle);

}

void Enemy01::Update()
{
	//If the enemy dies, stop updating collision bounds and set to 0.
	if (isDead == false)
	{
		m_CollisionRect = m_animated_sprite_.getGlobalBounds();
	}

	float pFrameTimer = C_SysContext::Get<FrameTimer>()->DeltaTime();

	m_CollisionRect = m_animated_sprite_.getGlobalBounds();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	sf::Vector2f tmove = sf::Vector2f(0, 0);
	// -------- --------------Enemy Movement Vectors -----------------------------------------------------

		//sf::Vector2f tup = sf::Vector2f(0.0f, -1.0f);
		//sf::Vector2f tdown = sf::Vector2f(0.0f, 1.0f);
		//sf::Vector2f tleft = sf::Vector2f(-1.0f, 0.0f);
		//sf::Vector2f tright = sf::Vector2f(1.0f, 0.0f);
	// -------- --------------Keyboard Input - Sprite Movement -----------------------------------------------------
		/*if (pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).OnPressed())*/
	if (isDead == false)
	{
		this->Fire();
	}
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown()) { tmove = tmove + tup; }
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown()) { tmove = tmove + tdown; }
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown()) { tmove = tmove + tleft; }
	//if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown()) { tmove = tmove + tright; }

	// -------- --------------Weapon Update ------------------------------------------------------------------

	m_pWeapon->SetPosition(m_animated_sprite_.getPosition().x + m_WeaponOffsetX *
		m_animated_sprite_.getScale().x, m_animated_sprite_.getPosition().y + m_WeaponOffsetY *
		m_animated_sprite_.getScale().y);

	m_pWeapon->SetScale(m_animated_sprite_.getScale().x, m_animated_sprite_.getScale().y);

	m_pWeapon->Update();

	m_animated_sprite_.move(tmove * 100.0f * pFrameTimer);

	m_animated_sprite_.Animate();

	if (Health <= 0)
	{
		isDead = true;
	}

	if (isDead == true)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

		this->m_animated_sprite_.SetVisible(false);
		m_pWeapon->m_AnimatedSprite.SetVisible(false);

		sf::FloatRect emptyfloatrect(0.0f, 0.0f, 0.0f, 0.0f);
		m_CollisionRect = emptyfloatrect;
	
		if (deadComplete == false)
		{
			eAudioManager->PlaySoundFX("sounds/sfx_precision_kill5.wav", false);
			Player* t_player;
			t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
			if (t_player)
			{
				t_player->ChangeScore(100.0f);
				deadComplete = true;
			}
		}
	}

}

void Enemy01::GetPosition(int & x, int & y)
{
	x = m_animated_sprite_.getPosition().x;
	y = m_animated_sprite_.getPosition().y;
}


void Enemy01::OnCollision(Collider2D* pCollider2D)
{
	if (pCollider2D->GetCollisionType() == CollisionType::E_PlayerBullet)
	{
		ChangeHealth(-1);
		eAudioManager->PlaySoundFX("sounds/sfx_impact_flesh4.wav", false);
		isDead = true;
	}

	else if (pCollider2D->GetCollisionType() == CollisionType::E_Player)
	{
		//Reached Player code here
		if (hasAttacked == false)
		{

			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

			Player* t_player;
			t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
			if (t_player)
			{
				t_player->ChangeHealth(-1);
				t_player->OnHit();
			}
			hasAttacked = true;
		}
	}
}

void Enemy01::ChangeHealth(int pint)
{
	Health += pint;
}

void Enemy01::Fire()
{

	//eAudioManager->PlaySoundFX("sounds/sfx_rifle3.wav", false);
	if (m_pWeapon)
	{
		m_pWeapon->Fire();
	}


}

void Enemy01::Reload()
{
	if (pInputDevice->GetButtonInput(E_DigitalInput_X).OnPressed())
	{
		if (m_pWeapon)
		{
			m_pWeapon->Reload();
		}
	}
}