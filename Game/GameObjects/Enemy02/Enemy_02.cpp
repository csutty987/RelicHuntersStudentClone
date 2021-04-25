#include "Enemy_02.h"



#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/GameState/GameState.h"

Enemy_02::Enemy_02()
	: Health(1)
{

}

Enemy_02::~Enemy_02()
{

}

void Enemy_02::Initialise()
{
	GameDataManager* p_GameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpriteSheetDef;
	pSpriteSheetDef = p_GameDataManager->GetSpritesheetDef("sprites/characters/spr_enemy.xml");

	this->m_EAnimatedSprite.AddAnimationFromSpriteSheetDef(E_IDLE, pSpriteSheetDef, "spr_enemy", 10);
	this->m_EAnimatedSprite.AddAnimationFromSpriteSheetDef(E_WALK, pSpriteSheetDef, "spr_enemy_weakspot", 10);
	this->m_EAnimatedSprite.AddAnimationFromSpriteSheetDef(E_SPRINT, pSpriteSheetDef, "spr_enemy_hit", 10);
	
	this->m_EAnimatedSprite.SetCurrentAnimation(E_IDLE);

	this->m_EAnimatedSprite.Animate();
}

void Enemy_02::Update()
{
	//If the enemy dies, stop updating collision bounds and set to 0.
	if (isDead == false)
	{
		m_CollisionRect = m_EAnimatedSprite.getGlobalBounds();
	}

	this->m_EAnimatedSprite.Animate();
	
	lengthCheck = isNear(500);

	if (lengthCheck == true)
	{
		this->Track(1);
	}
	
	if (Health <= 0)
	{
		isDead = true;
	}

	if (isDead == true)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
		this->m_EAnimatedSprite.SetVisible(false);
		Player* t_player;
		t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
		
		sf::FloatRect emptyfloatrect(0.0f, 0.0f, 0.0f, 0.0f);
		m_CollisionRect = emptyfloatrect;

		if (deadComplete == false)
		{
			eAudioManager->PlaySoundFX("sounds/sfx_precision_kill5.wav", false);
			t_player->ChangeScore(100.0f);
			deadComplete = true;
		}
	}

	this->isFar();


}

void Enemy_02::GetPosition(int & x, int & y)
{

	x = m_EAnimatedSprite.getPosition().x;
	y = m_EAnimatedSprite.getPosition().y;
}

void Enemy_02::SetPosition(const int px, const int py)
{
	this->m_EAnimatedSprite.setPosition(px, py);
	x_init_pos = px;
	y_init_pos = py;
}

void Enemy_02::Track(int p_speed)
{
	//Create a pointer to Game State Manager
	GameStateManager* m_GameStateManager = C_SysContext::Get<GameStateManager>();

	//Create blank ints for the vector
	int x;
	int y;

	//Get player position
	m_GameStateManager->GetCurrentGameState()->GetPlayer()->GetPosition(x, y);
	sf::Vector2f m_pos = sf::Vector2f(x, y);

	//Get enemy position
	int a;
	int b;
	Enemy_02::GetPosition(a, b);
	sf::Vector2f tempV = sf::Vector2f(a, b);

	//Get direction vector and apply speed to give the vector for motion
	sf::Vector2f posVect = (m_pos - tempV);
	sf::Vector2f dirVect = MathHelpers::Normalise(posVect);
	sf::Vector2f motion;
	int speed = p_speed;
	motion.x = dirVect.x * speed;
	motion.y = dirVect.y * speed;
	m_EAnimatedSprite.move(motion);

}

bool Enemy_02::isNear(float p_length)
{
	//Create a pointer to Game State Manager
	GameStateManager* m_GameStateManager = C_SysContext::Get<GameStateManager>();

	//Create blank ints for the vector
	int x;
	int y;

	//Get player position
	m_GameStateManager->GetCurrentGameState()->GetPlayer()->GetPosition(x, y);
	sf::Vector2f m_pos = sf::Vector2f(x, y);

	//Get enemy position
	int a;
	int b;
	Enemy_02::GetPosition(a, b);
	//a = m_EAnimatedSprite.getOrigin().x;
	//b = m_EAnimatedSprite.getOrigin().y;
	sf::Vector2f tempV = sf::Vector2f(a, b);

	//Get vector from enemy to player
	sf::Vector2f posVect = (m_pos - tempV);
	float lenght = MathHelpers::Length(posVect);

	//Checks if player is within given length and changes bool to true or false
	if (lenght < 0)
	{
		check = false;
	}
	if (lenght < p_length || (lenght > -p_length && lenght < 0))
	{
		check = true;
	}

	else
	{
		check = false;
	}
	
	return check;
}

void Enemy_02::OnCollision(Collider2D* pCollider2D)
{
	if (pCollider2D->GetCollisionType() == CollisionType::E_PlayerBullet)
	{
		ChangeHealth(-1);
		isDead = true;
	}

	if (pCollider2D->GetCollisionType() == CollisionType::E_Player)
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

			isDead = true;
			hasAttacked = true;
		}
	}
}

void Enemy_02::ChangeHealth(int pint)
{
	Health += pint;
	eAudioManager->PlaySoundFX("sounds/sfx_impact_flesh4.wav", false);
}

void Enemy_02::isFar()
{
	
	int t_x;
	int t_y;
	this->GetPosition(t_x,t_y);
	sf::Vector2f tempV = sf::Vector2f(t_x, t_y);
	sf::Vector2f originVect = sf::Vector2f(x_init_pos, y_init_pos);

	float length = MathHelpers::Length(tempV-originVect) ;
	if (length > 320)
	{
		m_EAnimatedSprite.setPosition(x_init_pos, y_init_pos);
	}
}


//void Enemy_02::CheckBounds()
//{
//	if (m_EAnimatedSprite.getPosition().x < l_max || m_EAnimatedSprite.getPosition().x > r_max)
//	{
//		this->m_EAnimatedSprite.setPosition(x_init_pos, y_init_pos);
//	}

//	if(m_EAnimatedSprite.getPosition().y < t_max || m_EAnimatedSprite.getPosition().y > b_max)
//	{
//		this->m_EAnimatedSprite.setPosition(x_init_pos, y_init_pos);
//	}
//}

