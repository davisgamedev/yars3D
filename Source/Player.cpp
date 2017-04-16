#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	playerMat = IDENTITY_M4; // Matrix for all player transformations
	playerPos = vector3(0.0f, 0.0f, 0.0f); // vec3 for player position, MAY NOT NEED THIS
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

	// apply tranlation to player matrix
	playerMat = glm::translate(playerMat, zIncrement);
}


// Move the player left and right
void Player::MoveHorizontal(float fIncrement) {
	// -X direction = left
	// +X direction = right

	// increment position in X direction
	vector3 xIncrement = vector3(fIncrement, 0.0f, 0.0f);

	// apply tranlation to player matrix
	playerMat = glm::translate(playerMat, xIncrement);
}

void Player::Shoot() {} // Shoot bullet

