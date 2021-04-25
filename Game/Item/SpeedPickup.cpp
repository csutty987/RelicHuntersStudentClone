#include "SpeedPickup.h"

SpeedPickup::SpeedPickup(int px, int py)
	:x_pos(px),
	y_pos(py)
{
}

SpeedPickup::~SpeedPickup()
{
	
}

void SpeedPickup::Initialise()
{

	sf::IntRect rect(0, 0, 62, 62);
	m_Frames.push_back(rect);

	sf::Vector2f origin(62 / 2, 62 / 2);
	m_Origins.push_back(origin);
	//Initialise the sprite
	m_Sprite.AddAnimation(1, "sprites/spr_infinity2_0.png", m_Frames, m_Origins, 10, true);
	m_Sprite.SetCurrentAnimation(1);
	
	//m_Sprite.Initialise("sprites/spr_infinity3_0.png", 500, 520, 62, 62, false);
	m_Sprite.setPosition(x_pos, y_pos);
	m_CollisionRect = m_Sprite.getGlobalBounds();
}

void SpeedPickup::Update()
{
	m_Sprite.Animate();
}

void SpeedPickup::GetPosition(int& x, int& y)
{
	m_Sprite.getPosition().x;
	m_Sprite.getPosition().y;
}

void SpeedPickup::SetPosition(int& x, int& y)
{
	m_Sprite.setPosition(x, y);
}


void SpeedPickup::OnCollision(Collider2D * pCollider2D)
{
	GameStateManager* pGameStatemanager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStatemanager->GetCurrentGameState();

	//WeaponBase
	
	//* pPlayer = C_SysContext::Get<Player>();

	if (pCollider2D->GetCollisionType() == E_Player)
	{
		if (SFXPlayed == false)
		{
			AudioManager* eAudioManager = C_SysContext::Get<AudioManager>();
			eAudioManager->PlaySoundFX("sounds/sfx_coin1.wav", false);
			SFXPlayed = true;
		}

		Player* t_player;
		t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
		if (t_player)
		{
			t_player->ChangeSpeed(200.0f);
			m_Sprite.SetVisible(false);
			pCurrentGameState->RemoveGameObject(this);
		}
	}
	
}

