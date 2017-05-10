#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false, bLastSpace = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	
	// Camera Movements
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		m_pCameraMngr->MoveVertical(fSpeed);



	// Player movement
	// else statements so player can only move in one direction at a time (no diagonal)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Move up
	{
		
		player->SetPlayerDirection(1); //Set direction
		if (player->killBullet->GetFired() == false) //Have kill bullet follow player
		{
			player->killBullet->ChangePosition(vector3(0.0f, 0.0f, (-fSpeed * 7)), player->GetPlayerPosition());
		}

		player->MoveVertical(-fSpeed * 7); // slower than horizontal speed
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Move down
	{
		player->SetPlayerDirection(3); //Set direction
		if (player->killBullet->GetFired() == false) //Have kill bullet follow player
		{
			player->killBullet->ChangePosition(vector3(0.0f, 0.0f, (fSpeed * 7)), player->GetPlayerPosition());
		}

		player->MoveVertical(fSpeed * 7);  // slower than horizontal speed
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Move left
	{
		player->SetPlayerDirection(2); //Set direction
		player->MoveHorizontal(-fSpeed * 10);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Move right
	{
		player->SetPlayerDirection(0); //Set direction
		player->MoveHorizontal(fSpeed * 10);
	}

	// Player Attack
	// only shoot if player is outside of the disruptor field
	if (player->getInFieldBool() == false && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && player->mainBullet->GetActiveBullet() == false) // Shoot Bullet
	{
		player->Shoot();
		sound.play();
	}

	//TEST KILL BULLET USING T -- Will be triggered by touching enemy core
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::T)) && player->killBullet->GetActiveBullet() == false) // Activate Kill Bullet
	{
		player->killBullet = new Bullet(playerPos, 1, 1);
		player->killBullet->SetActiveBullet(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) // TESTING STUFF
	{
		if (gameState == 1) {
			dead = true;
			gameState = 2;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // CHANGE GAME STATE
	{
		if (gameState == 0) {
			gameState = 1;
		}
		else if (gameState == 2) {
			win = false;
			dead = false;
			gameState = 1;
		}
	}
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
