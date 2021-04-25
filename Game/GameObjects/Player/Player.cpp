#include "Player.h"
#include <iostream>

Player::Player()
:isMoving(false)
, PlayerHealth(3)
, PlayerSpeed(160.0f)
, PlayerScore(0)
, isDead(false)
, EnemiesHit(0)
{	
}

Player::~Player()
{
	SAFE_DELETE_PTR(m_pWeapon);
	SAFE_DELETE_PTR(m_pShotgun);
}

void Player::Initialise()
{
	m_AnimatedSprite.setPosition(250, 500);
	
	// -------- Set Up the Animation Sprite Sheet XML --------
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_jimmy.xml");

	// -------- Populate the Animation State --------
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateIdle, pSpritesheetDef, "spr_jimmy_idle", 24);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateSprint, pSpritesheetDef, "spr_jimmy_sprint", 24);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateWalk, pSpritesheetDef, "spr_jimmy_walk", 24);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateDash, pSpritesheetDef, "spr_jimmy_dash", 24, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateHit, pSpritesheetDef, "spr_jimmy_hit", 24, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateMelee, pSpritesheetDef, "spr_jimmy_melee", 24, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationStateDeath, pSpritesheetDef, "spr_jimmy_death", 24, false);

	// -------- Sets the Default Animation --------
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateIdle);

	//Setup Global Bounds of Sprite
	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	// ------ Initialise Player Weapons ------
	m_pWeapon = new BlitzWeapon();
	m_pShotgun = new Shotgun();

	m_pEquippedWeapon = m_pWeapon;
	m_pEquippedWeapon->Initialise();

	//walk sfx initialise
	walkBuffer.loadFromFile("sounds/sfx_walk4.wav");
	Walk.setBuffer(walkBuffer);

	//Melee
	meleeBuffer.loadFromFile("sounds/sfx_melee.wav");
	melee.setBuffer(meleeBuffer);

	//Dash
	dashBuffer.loadFromFile("sounds/sfx_dash3.wav");
	dash.setBuffer(dashBuffer);

	//Shotgun Reload
	sReloadBuffer.loadFromFile("sounds/sfx_ammo2.wav");
	sReload.setBuffer(sReloadBuffer);
	//Rifle Reload
	rReloadBuffer.loadFromFile("sounds/sfx_ammo1.wav");
	rReload.setBuffer(rReloadBuffer);

}

void Player::Update()
{
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	PlayerMovement();
	UpdateWeapon();
	WeaponManager();
	StillAlive();

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	switch (m_AnimatedSprite.GetCurrentAnimation())
	{
	case E_AnimationStateDash:
	{
		if (isMoving)
		{
			setSpeed(300);
			if (m_AnimatedSprite.AnimationFinished())
			{
				setSpeed(160);
				//pAudioManager->PlaySoundFX("sounds/sfx_dash3.wav", false);
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateIdle);
			}
		}
	}
	break;
	case E_AnimationStateDeath:
	{
		if (m_AnimatedSprite.AnimationFinished())
		{
			isDead = true;
		}
	}
	break;
	case E_AnimationStateHit:
	{
		if (m_AnimatedSprite.AnimationFinished())
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateIdle);
		}
	}
	break;
	case E_AnimationStateIdle:
	{
		if (isMoving)
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateWalk);
		}
	}
	break;
	case E_AnimationStateMelee:
	{
		if (m_AnimatedSprite.AnimationFinished())
		{
			//pAudioManager->PlaySoundFX("sounds/sfx_melee.wav", false);
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateIdle);
		}
	}
	break;
	case E_AnimationStateSprint:
	{
		/*if (isMoving)
		{
			setSpeed(250);
			if (pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsUp())
			{
				setSpeed(160);
			}
		}*/
	}
	break;
	case E_AnimationStateWalk:
	{
		//PlaySFX("sounds/sfx_walk4.wav");
		if (!isMoving)
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateIdle);
		}

	}
	break;

	default:
	{
		//error
	}
	break;
	}

	m_AnimatedSprite.Animate();

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	if (PlayerHealth <= 0)
	{
		isDead = true;
	}

}

void Player::UpdateWeapon()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	float angle = 0.0f;

	if (pInputDevice)
	{
		float RightStickXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
		float RightStickYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

		sf::Vector2f Up(0.0f, -1.0f);
		sf::Vector2f Forwards(RightStickXPos, RightStickYPos);

		angle = MathHelpers::AngleBetweenVectors(Up, Forwards) - 90.0f;

		//m_Crosshair.Initialise("sprites/weapons/spr_crosshair2_1.png", RightStickXPos, RightStickYPos, 1, 1, true);
	}

	//inverting angle due to using .scale to flip the player when they turn left and right
	angle = m_AnimatedSprite.getScale().x < 0.0f ? -angle : angle;

	// ---- Update Weapon based on player location----
	m_pEquippedWeapon->SetPosition(m_AnimatedSprite.getPosition().x + m_WeaponOffsetX * m_AnimatedSprite.getScale().x, (m_AnimatedSprite.getPosition().y + 30) + m_WeaponOffsetY * m_AnimatedSprite.getScale().y);
	m_pEquippedWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);
	m_pEquippedWeapon->SetRotation(angle);
	m_pEquippedWeapon->Update();

}

void Player::PlayerMovement()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	isMoving = false;

	if (isDead == true)
	{
		
		//any additional changes to player on death here
	}

	// -------- Player Movement Vectors --------
	sf::Vector2f tup = sf::Vector2f(0.0f, -PlayerSpeed * pFrameTimer->DeltaTime());
	sf::Vector2f tdown = sf::Vector2f(0.0f,PlayerSpeed * pFrameTimer->DeltaTime());
	sf::Vector2f tleft = sf::Vector2f(-PlayerSpeed * pFrameTimer->DeltaTime(), 0.0f);
	sf::Vector2f tright = sf::Vector2f(PlayerSpeed * pFrameTimer->DeltaTime(), 0.0f);

	//handle player movement controls

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		m_AnimatedSprite.move(tup);
		isMoving = true;

	}
	/*if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsUp())
	{
		i = 0;
	}*/

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		m_AnimatedSprite.move(tdown);
		isMoving = true;

	}
	/*if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsUp())
	{
		i = 0;
	}*/

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		m_AnimatedSprite.move(tleft);
		isMoving = true;

	}
	/*if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsUp())
	{
		i = 0;
	}*/

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		m_AnimatedSprite.move(tright);
		isMoving = true;

	}

	/*if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsUp())
	{
		i = 0;
	}*/

	//Initialise SoundFX

	if (isMoving == true)
	{
		for (i; i < 1; i++)
		{
			//pAudioManager->PlaySoundFX("sounds/sfx_walk4.wav", true);
			Walk.setLoop(true);
			Walk.play();
		}
	}

	if (!isMoving)
	{
		i = 0;
		Walk.setLoop(false);
		Walk.stop();

	}

	

	//Special Moves
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_B).IsDown())
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateMelee);
		for (a; a < 1; a++)
		{
			melee.play();
		}
	}
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_B).IsUp())
	{
		a = 0;
	}

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_A).IsDown())
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateDash);
		for (b; b < 1; b++)
		{
			dash.play();
		}
	}
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_A).IsUp())
	{
		b = 0;
	}

	/*if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateSprint);
	}*/

	//manage collision with walls

	if (up_tilenum != -1/* && pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown()*/)
	{
		m_AnimatedSprite.move(tup);
	}

	if (down_tilenum != -1/* && pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown()*/)
	{
		m_AnimatedSprite.move(tdown);
	}

	if (left_tilenum != -1/* && pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown()*/)
	{
		m_AnimatedSprite.move(tright);
	}

	if (right_tilenum != -1/* && pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown()*/)
	{
		m_AnimatedSprite.move(tleft);
	}

	//flip player to point to where the mouse is pointing

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() > 0.0f)
	{
		m_AnimatedSprite.setScale(1.0f, 1.0f);
	}
	else if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() < 0.0f)
	{
		m_AnimatedSprite.setScale(-1.0f, 1.0f);
	}

}

void Player::setSpeed(float pfloat)
{
	PlayerSpeed = pfloat;
}

void Player::SetSurroundingTileNum(int uptilenum, int downtilenum, int lefttilenum, int righttilenum)
{
	up_tilenum = uptilenum;
	down_tilenum = downtilenum;
	left_tilenum = lefttilenum;
	right_tilenum = righttilenum;
}

void Player::SetPlayerTileNum(int tilenum)
{
	p_tilenum = tilenum;
}

void Player::WeaponManager()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//Fire
	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_RightTrigger).GetValue() >= 0.1f)
	{
		m_pEquippedWeapon->Fire();
	}

	//Weapon Reload
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_X).IsDown())
	{
		m_pEquippedWeapon->Reload();

		if (WeaponShotgun == true)
		{
			for (c; c < 1; c++)
			{
				sReload.play();
			}
		}
		else if (WeaponShotgun == false) {
			for (d; d < 1; d++)
			{
				rReload.play();
			}

		}
	}
	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_X).IsUp())
	{
		rReload.stop();
		sReload.stop();
		c = 0;
		d = 0;
	}

	//Weapon Switching
	
	if (weaponSwitch == true && pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_Y).IsDown())
	{
		m_pWeapon->m_AnimatedSprite.SetVisible(false);
		m_pEquippedWeapon = m_pShotgun;
		m_pEquippedWeapon->Initialise();
		m_pShotgun->m_AnimatedSprite.SetVisible(true);
		weaponSwitch = false;
		WeaponShotgun = true;

		m_pEquippedWeapon->SetReload(0);

	}
	
	if (weaponSwitch == false && pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_LeftShoulder).IsDown())
	{

		m_pShotgun->m_AnimatedSprite.SetVisible(false);
		m_pEquippedWeapon = m_pWeapon;
		m_pEquippedWeapon->Initialise();
		m_pWeapon->m_AnimatedSprite.SetVisible(true);
		weaponSwitch = true;
		WeaponShotgun = false;

		m_pEquippedWeapon->SetReload(0);

	}


}

void Player::ChangeScore(int pscore)
{
	PlayerScore += pscore;
}

void Player::OnHit()
{
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateHit);

	pAudioManager->PlaySoundFX("sounds/sfx_hit_taken3.wav", false);
	StillAlive();
}

void Player::StillAlive()
{
	if (PlayerHealth <= 0)
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationStateDeath);
		pAudioManager->PlaySoundFX("sounds/sfx_duck_death.wav", false);
	}
}

void Player::GetPosition(int& x, int & y)
{
	x = m_AnimatedSprite.getPosition().x;
	y = m_AnimatedSprite.getPosition().y;
}

void Player::Fire()
{

	if (m_pWeapon)
	{
		m_pWeapon->Fire();
	}
}

void Player::Reload()
{
	if (m_pWeapon)
	{
		m_pWeapon->Reload();
	}
}
void Player::OnCollision(Collider2D* pCollider2D)
{
	if (pCollider2D->GetCollisionType() == CollisionType::E_EnemyBullet)
	{

		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

		ChangeHealth(-1);
		OnHit();
	}
	if (pCollider2D->GetCollisionType() == E_HP)
	{
		ChangeHealth(1);
	}
	if (pCollider2D->GetCollisionType() == E_SP)
	{
		setSpeed(190);
	}
}


void Player::ChangeHealth(int pint)
{

	PlayerHealth += pint;
	
}

void Player::ChangeSpeed(float pfloat)
{
	PlayerSpeed = +pfloat;
}

void Player::ChangeEnemiesHit(int hitCount)
{
	EnemiesHit = +hitCount;
}
