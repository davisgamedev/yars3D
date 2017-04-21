#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	playerMat = IDENTITY_M4; // Matrix for all player transformations
	playerPos = vector3(0.0f, 0.0f, 0.0f); // vec3 for player position, MAY NOT NEED THIS

	mainBullet = new Bullet(playerPos,playerDir, 0); //Create initial bullet
	killBullet = new Bullet(playerPos, playerDir, 1); //Create initial bullet
}


Player::~Player()
{
}

// Get the Player's transformation matrix
matrix4 Player::GetPlayerMatrix() {
	return playerMat;
}


// Move the player up and down
void Player::MoveVertical(float fIncrement) {
	// -Z direction = up
	// +Z direction = down
	
	// increment position in Z direction
	vector3 zIncrement = vector3(0.0f, 0.0f, fIncrement);
	playerPos += zIncrement;

	// apply tranlation to player matrix
	playerMat = glm::translate(playerMat, zIncrement);
}


// Move the player left and right
void Player::MoveHorizontal(float fIncrement) {
	// -X direction = left
	// +X direction = right

	// increment position in X direction
	vector3 xIncrement = vector3(fIncrement, 0.0f, 0.0f);
	playerPos += xIncrement;
	// apply tranlation to player matrix
	playerMat = glm::translate(playerMat, xIncrement);
}

vector3 Player::GetPlayerPosition() {
	return playerPos;
}

int Player::GetPlayerDirection() {
	return playerDir;
}

void Player::SetPlayerDirection(int dir) {
	playerDir = dir;
}

void Player::Shoot() // Shoot bullet
{
	if (killBullet->GetActiveBullet() == true && killBullet->GetFired() == false) // Kill Bullet
	{
		killBullet->SetFired(true);
	}
	else //Main Bullet 
	{
		mainBullet = new Bullet(playerPos, playerDir, 0);
		mainBullet->SetActiveBullet(true);
		mainBullet->SetFired(true);
	}
}

