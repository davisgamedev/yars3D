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

Enemy::~Enemy()
{
	SafeDelete(enemyBullet);
}
