#include "Enemy.h"

Enemy* Enemy::instance = nullptr;

// create a new enemy instance
Enemy::Enemy()
{
	enemyPos = vector3(5.0f, 0.0f, -1.25f);
	enemyMatrix = glm::translate(enemyPos);
	active = true;
	counter = 1;
	direction = true;
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

		// increment the counter each frame
		counter++;
	}
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
}
