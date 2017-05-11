#include "Enemy.h"

Enemy* Enemy::instance = nullptr;

// create a new enemy instance
Enemy::Enemy()
{
	enemyPos = vector3(9.0f, 0.0f, -1.25f);
	enemyMatrix = glm::translate(enemyPos);
	active = true;
	counter = 1;
	counterFire = 1;
	direction = true;
	launched = false;
	firing = false;
	fireTiming = (rand() % 500 + 200);
	spin = 0;
	enemyLength = 0.7f;
	enemyLives = 1;
	Reset();
}

void Enemy::GenerateModel(vector3 color) {
	if (voxelList == nullptr) {
		voxelList = new PrimitiveClass[NUM_VOXELS];
		for (int i = 0; i < NUM_VOXELS; i++) {
			voxelList[i] = *(new PrimitiveClass());
			voxelList[i].GenerateCube(SIZE_VOXELS, color);
			//renderVoxels[i] = true;
		}
	}
}

void Enemy::RenderModel(matrix4 projection, matrix4 view) {
	int i = 0;
	for (int h = 0; h < BARRIER_H; h++) {
		for (int w = 0; w < BARRIER_W; w++) {
			if (!barrierVals[h][w]) continue;
			//if (renderVoxels[i] == true) {
				vector3 voxelPos = vector3(w * SIZE_VOXELS, 0.0f, h * SIZE_VOXELS);
				matrix4 localMat = glm::translate(IDENTITY_M4, (enemyPos - BARRIER_COMP) + voxelPos);
				voxelList[i++].Render(projection, view, localMat);
			//}
			//else {

			//}
			
		}
	}
}

void Enemy::Reset() {
	if (voxelList == nullptr) GenerateModel(REBROWN);
	for (int h = 0; h < BARRIER_H; h++) {
		for (int w = 0; w < BARRIER_W; w++) {
			barrierVals[h][w] = BARRIER_REF[h][w];
		}
	}
}

// move the enemy back and forth while the level is in progress and the enemy is "active"
void Enemy::Move()
{
	if (active == true)
	{
		if (direction == true)
		{
			enemyPos += vector3(0.0f, 0.0f, 0.01f);
			enemyMatrix = glm::translate(enemyPos);
		}
		if (direction == false)
		{
			enemyPos -= vector3(0.0f, 0.0f, 0.01f);
			enemyMatrix = glm::translate(enemyPos);
		}
		if (counter > 250)
		{
			// if the counter gets above a certain point, set it back to 0 and switch direction
			direction = !direction;
			counter = 0;
		}

		// increment the counters each frame
		counter++;
		counterFire++;

		//Start Spinning before launching
		if ((counterFire > (fireTiming * .65f)))
		{
			spin = spin + 10;
			enemyMatrix = glm::rotate(enemyMatrix, spin, vector3(0.0f, 1.0f, 0.0f));
		}

		//Decide when to Shoot
		if (counterFire == fireTiming && firing == false)
		{
			firing = true;
			counterFire = 1;
			fireTiming = (rand() % 500 + 200);
		} 

		
	}

	
}

vector3 Enemy::GetVoxelPosition(int r, int c) {
	
	float x = (enemyPos.x - BARRIER_COMP.x) + (c * SIZE_VOXELS);
	float z = (enemyPos.z - BARRIER_COMP.z) + (r * SIZE_VOXELS);
	
	return vector3(x, 0.0f, z);
}

void Enemy::DetectBarrierCollisions(Bullet* playerBullet, Player* player)
{
	// get locations of the bullet to check and player to check
	vector3 bulletPos = playerBullet->GetBulletPos();
	float bulletLength = playerBullet->GetBulletLength();
	vector3 playerPos = player->GetPlayerPosition();
	float playerLength = player->getPlayerLength();
	int type = playerBullet->GetBulletType();

	// only check collisions between barrier and bullet types of 0 and 1
	if (type == 0 || type == 1) {

		for (int i = 0; i < BARRIER_H; i++) {
			for (int j = 0; j < BARRIER_W; j++) {
				vector3 voxelPos = GetVoxelPosition(i, j);
					if (barrierVals[i][j] == 0) {
						continue;
					}
					if ((((playerPos.x - (playerLength / 2) > voxelPos.x - (SIZE_VOXELS / 2)) && (playerPos.x - (playerLength / 2) < voxelPos.x + (SIZE_VOXELS / 2))) || ((playerPos.x + (playerLength / 2) > voxelPos.x - (SIZE_VOXELS / 2)) && (playerPos.x + (playerLength / 2) < voxelPos.x + (SIZE_VOXELS / 2)))) && (((playerPos.z - (playerLength / 2) > voxelPos.z - (SIZE_VOXELS / 2)) && (playerPos.z - (playerLength / 2) < voxelPos.z + (SIZE_VOXELS / 2))) || ((playerPos.z + (playerLength / 2) > voxelPos.z - (SIZE_VOXELS / 2)) && (playerPos.z + (playerLength / 2) < voxelPos.z + (SIZE_VOXELS / 2))))) {
						barrierVals[i][j] = 0;
						player->SetPlayerScore(10);
					}
					else if((((bulletPos.x - (bulletLength / 2) > voxelPos.x - (SIZE_VOXELS / 2)) && (bulletPos.x - (bulletLength / 2) < voxelPos.x + (SIZE_VOXELS / 2))) || ((bulletPos.x + (bulletLength / 2) > voxelPos.x - (SIZE_VOXELS / 2)) && (bulletPos.x + (bulletLength / 2) < voxelPos.x + (SIZE_VOXELS / 2)))) && (((bulletPos.z - (bulletLength / 2) > voxelPos.z - (SIZE_VOXELS / 2)) && (bulletPos.z - (bulletLength / 2) < voxelPos.z + (SIZE_VOXELS / 2))) || ((bulletPos.z + (bulletLength / 2) > voxelPos.z - (SIZE_VOXELS / 2)) && (bulletPos.z + (bulletLength / 2) < voxelPos.z + (SIZE_VOXELS / 2))))){
						barrierVals[i][j] = 0;
						playerBullet->SetFired(false);
						playerBullet->SetActiveBullet(false);
						playerBullet->ResetPosition();
						//player->killBullet->SetFired(false);
						//player->killBullet->SetActiveBullet(false);
					}
					else {
						// do nothing
					}
			}
		}
		
	}

	// check if current bullet pos or player pos are "hitting" a voxel in barrier

	
}

void Enemy::DetectEnemyCollisions(Player* player)
{
	vector3 playerPos = player->GetPlayerPosition();
	float playerLength = player->getPlayerLength();
	/*
	if ((((playerPos.x - (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x - (playerLength / 2) < enemyPos.x + (enemyLength / 2))) || ((playerPos.x + (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x + (playerLength / 2) < enemyPos.x + (enemyLength / 2)))) && (((playerPos.z - (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z - (playerLength / 2) < enemyPos.z + (enemyLength / 2))) || ((playerPos.z + (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z + (playerLength / 2) < enemyPos.z + (enemyLength / 2))))) {
		player->killBullet = new Bullet(playerPos, 1, 1);
		player->killBullet->SetActiveBullet(true);
		player->SetLives();
	}
	else {
		// do nothing
	}
	*/
	
	if (launched == false && (((playerPos.x - (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x - (playerLength / 2) < enemyPos.x + (enemyLength / 2))) || ((playerPos.x + (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x + (playerLength / 2) < enemyPos.x + (enemyLength / 2)))) && (((playerPos.z - (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z - (playerLength / 2) < enemyPos.z + (enemyLength / 2))) || ((playerPos.z + (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z + (playerLength / 2) < enemyPos.z + (enemyLength / 2))))) {
		// colliding
		player->killBullet = new Bullet(playerPos, 1, 1);
		player->killBullet->SetActiveBullet(true);
		
	}
	else if (launched == true && (((playerPos.x - (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x - (playerLength / 2) < enemyPos.x + (enemyLength / 2))) || ((playerPos.x + (playerLength / 2) > enemyPos.x - (enemyLength / 2)) && (playerPos.x + (playerLength / 2) < enemyPos.x + (enemyLength / 2)))) && (((playerPos.z - (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z - (playerLength / 2) < enemyPos.z + (enemyLength / 2))) || ((playerPos.z + (playerLength / 2) > enemyPos.z - (enemyLength / 2)) && (playerPos.z + (playerLength / 2) < enemyPos.z + (enemyLength / 2))))) {
		
		player->SetLives();
	}
	else {
		// do nothing
	}
	

	
}

void Enemy::DetectEnemyKillShot(Bullet* bullet, Player* player)
{
	int type = bullet->GetBulletType();
	vector3 bulletPos = bullet->GetBulletPos();
	float bulletLength = bullet->GetBulletLength();
	bool active = bullet->GetActiveBullet();

	// if bullet type is kill bullet, detect collisions with enemy
	if (type == 1 && active == true && launched == false)
	{
		if ((((bulletPos.x - (bulletLength / 2) > enemyPos.x - (enemyLength / 2)) && (bulletPos.x - (bulletLength / 2) < enemyPos.x + (enemyLength / 2))) || ((bulletPos.x + (bulletLength / 2) > enemyPos.x - (enemyLength / 2)) && (bulletPos.x + (bulletLength / 2) < enemyPos.x + (enemyLength / 2)))) && (((bulletPos.z - (bulletLength / 2) > enemyPos.z - (enemyLength / 2)) && (bulletPos.z - (bulletLength / 2) < enemyPos.z + (enemyLength / 2))) || ((bulletPos.z + (bulletLength / 2) > enemyPos.z - (enemyLength / 2)) && (bulletPos.z + (bulletLength / 2) < enemyPos.z + (enemyLength / 2))))) {
			// colliding
			player->SetPlayerScore(1000);
			enemyLives = 0;
		}
		else {
			// do nothing
		}
	}
}

void Enemy::Shoot()
{
	launched = true;
}

void Enemy::EndLaunch()
{
	launched = false;
}

bool Enemy::GetLaunch()
{
	return launched;
}

bool Enemy::GetFiring()
{
	return firing;
}

void Enemy::SetFiring(bool setFire)
{
	firing = setFire;
}

vector3 Enemy::GetPosition()
{
	return enemyPos;
}

matrix4 Enemy::GetMatrix()
{
	return enemyMatrix;
}

int Enemy::getEnemyLives() {
	return enemyLives;
}

Enemy::~Enemy()
{
	if (voxelList != nullptr) {
		delete[] voxelList;
		voxelList = nullptr;
	}
	SafeDelete(enemyBullet);
}
