#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	playerMat = IDENTITY_M4; // Matrix for all player transformations
	playerPos = vector3(0.0f, 0.0f, 0.0f); // vec3 for player position, MAY NOT NEED THIS

	mainBullet = new Bullet(playerPos,playerDir, 0); //Create initial bullet
	killBullet = new Bullet(playerPos, playerDir, 1); //Create initial bullet

	verticalBoundary = 4.0f; // set max/min vertical boundary (z axis)
	horizontalBoundary = 6.5f; // set max/min horizontal boudnary (x axis)

}


Player::~Player()
{
	if (voxelList != nullptr) {
		delete[] voxelList;
		voxelList = nullptr;
	}
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

	Moving = true;
	WrapPlayer();
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

	// Check for horizontal boundary, prevent player from moving outside of it
	if (playerPos.x > horizontalBoundary) { // Right Boundary
		playerPos.x = horizontalBoundary;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
		
	}
	else if (playerPos.x < -horizontalBoundary) { // Left Boundary
		playerPos.x = -horizontalBoundary;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}

	Moving = true;
}

vector3 Player::GetPlayerPosition() { // return player's position
	return playerPos;
}

int Player::GetPlayerDirection() { // return player's direction
	return playerDir;
}

void Player::SetPlayerDirection(int dir) { // set player's direction
	playerDir = dir;
	// Don't want to change rotation every frame, just when it's direction changes
	/*
	if (playerDir = 0) { // UP
		playerMat = glm::rotate(playerMat, -1.0f, vector3(0.0f, 1.0f, 0.0f));
		//glm::rotate(player)
	}
	else if (playerDir = 1) { // RIGHT
		playerMat = glm::rotate(playerMat, 1.0f, vector3(0.0f, 1.0f, 0.0f));
	}
	else if (playerDir = 2) { // DOWN
		playerMat = glm::rotate(playerMat, 1.0f, vector3(0.0f, 1.0f, 0.0f));
	}
	else if (playerDir = 3) { // LEFT
		playerMat = glm::rotate(playerMat, -1.0f, vector3(0.0f, 1.0f, 0.0f));
	}
	*/
}

void Player::Shoot() // Shoot bullet
{
	if (killBullet->GetActiveBullet() == false || killBullet->GetFired() == true) // Kill Bullet
	{
		mainBullet = new Bullet(playerPos, playerDir, 0);
		mainBullet->SetActiveBullet(true);
		mainBullet->SetFired(true);
	}
	else if (killBullet->GetActiveBullet() == true && killBullet->GetFired() == false)//Main Bullet 
	{
		killBullet->SetFired(true);
	}
}

void Player::WrapPlayer() { // Wraps player on vertical axis
	if (playerPos.z > verticalBoundary) {
		playerPos.z = -verticalBoundary;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}
	else if (playerPos.z < -verticalBoundary) {
		playerPos.z = verticalBoundary;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}
}

void Player::GenerateModel(vector3 color) {
	if (voxelList == nullptr) {
		voxelList = new PrimitiveClass[NUM_VOXELS];
		for (int i = 0; i < NUM_VOXELS; i++) {
			voxelList[i] = *(new PrimitiveClass());
			voxelList[i].GenerateCube(SIZE_VOXELS, color);
		}
	}
}

void Player::Render(matrix4 projection, matrix4 view, matrix4 world, bool movingFrame) {
	if (voxelList != nullptr) {
		for (int i = 0; i < NUM_VOXELS; i++) {
			if(!movingFrame || !Moving)
				voxelList[i].Render(projection, view, world * voxelMatrixList1[i]);
			else
				voxelList[i].Render(projection, view, world * voxelMatrixList2[i]);
		}
	}

	Moving = false;
}