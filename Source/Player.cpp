#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	playerMat = IDENTITY_M4; // Matrix for all player transformations
	playerPos = vector3(0.0f, 0.0f, 0.0f); // vec3 for player position, MAY NOT NEED THIS
	rotationMat = IDENTITY_M4;

	mainBullet = new Bullet(playerPos,playerDir, 0); //Create initial bullet
	killBullet = new Bullet(playerPos, playerDir, 1); //Create initial bullet

	verticalBoundaryTop = 5.0f; // set max/min vertical boundary (z axis)
	verticalBoundaryBottom = 5.75f; // set max/min vertical boundary (z axis)
	horizontalBoundaryLeft = 9.35f; // set max/min horizontal boudnary (x axis)
	horizontalBoundaryRight = 9.15f; // set max/min horizontal boudnary (x axis)
	prevPlayerDir = 1;
	playerDir = 1;
	inField = false;

	playerLength = 0.8f;
	playerLives = 1;
	playerScore = 0;
}


Player::~Player()
{
	if (voxelList != nullptr) {
		delete[] voxelList;
		voxelList = nullptr;
	}
	SafeDelete(mainBullet);
	SafeDelete(killBullet);
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
	if (playerPos.x > horizontalBoundaryRight) { // Right Boundary
		playerPos.x = horizontalBoundaryRight;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}
	else if (playerPos.x < -horizontalBoundaryLeft) { // Left Boundary
		playerPos.x = -horizontalBoundaryLeft;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}

	// Check if player is in the disruptor field
	if (playerPos.x >= -3.5f && playerPos.x <= 0.5f) {
		inField = true;
	}
	else {
		inField = false;
	}

	Moving = true;
}

void Player::DetectCollisions(Bullet* bullet)
{
	vector3 bulletPos = bullet->GetBulletPos();
	float bulletLength = bullet->GetBulletLength();
	int type = bullet->GetBulletType();
	//std::cout << " bullx: " << bulletPos.x;
	//std::cout << " bully: " << bulletPos.y;
	//std::cout << " bullz: " << bulletPos.z;
	//std::cout << (((playerPos.x - (playerLength / 2) > bulletPos.x - (bulletLength / 2)) && (playerPos.x - (playerLength / 2) < bulletPos.x + (bulletLength / 2))) || ((playerPos.x + (playerLength / 2) > bulletPos.x - (bulletLength / 2)) && (playerPos.x + (playerLength / 2) < bulletPos.x + (bulletLength / 2)))) && (((playerPos.z - (playerLength / 2) > bulletPos.z - (bulletLength / 2)) && (playerPos.z - (playerLength / 2) < bulletPos.z + (bulletLength / 2))) || ((playerPos.z + (playerLength / 2) > bulletPos.z - (bulletLength / 2)) && (playerPos.z + (playerLength / 2) < bulletPos.z + (bulletLength / 2))));
	if (type == 2 && inField == true) {
		return;
	}
	if (type != 0) {

		if ((((playerPos.x - (playerLength / 2) > bulletPos.x - (bulletLength / 2)) && (playerPos.x - (playerLength / 2) < bulletPos.x + (bulletLength / 2))) || ((playerPos.x + (playerLength / 2) > bulletPos.x - (bulletLength / 2)) && (playerPos.x + (playerLength / 2) < bulletPos.x + (bulletLength / 2)))) && (((playerPos.z - (playerLength / 2) > bulletPos.z - (bulletLength / 2)) && (playerPos.z - (playerLength / 2) < bulletPos.z + (bulletLength / 2))) || ((playerPos.z + (playerLength / 2) > bulletPos.z - (bulletLength / 2)) && (playerPos.z + (playerLength / 2) < bulletPos.z + (bulletLength / 2))))) {
			// colliding
			playerLives--;

		}
		else {
			// not colliding
		}
	}

	
}

vector3 Player::GetPlayerPosition() { // return player's position
	return playerPos;
}

int Player::GetPlayerDirection() { // return player's direction
	return playerDir;
}

void Player::SetPlayerDirection(int dir) { // set player's direction
	playerDir = dir;
	rotationMat = glm::rotate(IDENTITY_M4, ((float)dir * 90.0f), vector3(0.0f, 1.0f, 0.0f));
}

int Player::GetPrevPlayerDirection() { // return player's direction
	return prevPlayerDir;
}

void Player::SetPrevPlayerDirection(int prevDir) { // set player's direction
	prevPlayerDir = prevDir;
	//rotationMat = glm::rotate(IDENTITY_M4, ((float)dir * 90.0f), vector3(0.0f, 1.0f, 0.0f));

}

void Player::Shoot() // Shoot bullet
{
	// only shoot player bullet or kill bullet if player is not in the disruptor field
	if (inField == false) {
		if (killBullet->GetActiveBullet() == false || killBullet->GetFired() == true) // Kill Bullet
		{
			mainBullet = new Bullet(playerPos, (playerDir+3)%4, 0);
			mainBullet->SetActiveBullet(true);
			mainBullet->SetFired(true);
		}
		else if (killBullet->GetActiveBullet() == true && killBullet->GetFired() == false)//Main Bullet 
		{
			killBullet->SetFired(true);
		}
	}
}

void Player::WrapPlayer() { // Wraps player on vertical axis
	if (playerPos.z > verticalBoundaryBottom) {
		playerPos.z = -verticalBoundaryTop;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}
	else if (playerPos.z < -verticalBoundaryTop) {
		playerPos.z = verticalBoundaryBottom;
		playerMat = glm::translate(IDENTITY_M4, playerPos);
	}
}

void Player::setInFieldBool(bool inFld) { // set in Field bool
	inField = inFld;
}

bool Player::getInFieldBool() { // get in Field bool
	return inField;
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
			if (!movingFrame || !Moving) {
				voxelList[i].Render(projection, view, world * rotationMat * voxelMatrixList1[i]);
			}
			else{
				voxelList[i].Render(projection, view, world * rotationMat * voxelMatrixList2[i]);
			}
		}
	}

	Moving = false;
}

int Player::getPlayerLives() {
	return playerLives;
}

float Player::getPlayerLength() {
	return playerLength;
}

void Player::SetLives() {
	playerLives--;
}

int Player::GetPlayerScore() {
	return playerScore;
}

void Player::SetPlayerScore(int addScore) {
	playerScore += addScore;
}