#include "HealthPickup.h"


#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/System/GameState/GameState.h"

HealthPickup::HealthPickup(int px, int py)
{
}

HealthPickup::~HealthPickup()
{
}
void HealthPickup::Initialise()
{
	sf::IntRect rect(0, 0, 62, 62);
	m_Frames.push_back(rect);

	sf::Vector2f origin(62 / 2, 62 / 2);
	m_Origins.push_back(origin);
	//Initialise the sprite
	m_Sprite.AddAnimation(1, "sprites/spr_infinity2_0.png", m_Frames, m_Origins, 10, true);
	//m_Sprite.Initialise("sprites/spr_infinity2_0.png", 0, 0, 62, 62, false);
	m_Sprite.SetCurrentAnimation(1);
	m_Sprite.setPosition(800, 800);
	m_CollisionRect = m_Sprite.getGlobalBounds();
}


void HealthPickup::Update()
{
	m_Sprite.Animate();
	//m_CollisionRect = m_Sprite.getGlobalBounds();
}

void HealthPickup::GetPosition(int& x, int& y)
{
	m_Sprite.getPosition().x;
	m_Sprite.getPosition().y;
}

void HealthPickup::SetPosition(int& x, int& y)
{
	m_Sprite.setPosition(x, y);
}

void HealthPickup::OnCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	if (pCollider2D->GetCollisionType() == E_Player)
	{
		if (SFXPlayed = false)
		{
			AudioManager* eAudioManager = C_SysContext::Get<AudioManager>();
			eAudioManager->PlaySoundFX("sounds/sfx_pickup_health.wav", false);
			SFXPlayed = true;
		}

		m_Sprite.SetVisible(false);
		Player* t_player;
		t_player = dynamic_cast<Player*>(pCurrentGameState->GetPlayer());
		if (t_player)
		{
			t_player->ChangeHealth(1);
		}

		pCurrentGameState->RemoveGameObject(this);
	}

	//pCurrentGameState->DetailedGetPlayer()->ChangeHealth(1);
}
