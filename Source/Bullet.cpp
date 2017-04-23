#include "Bullet.h"
#include <stdio.h>


// Constructor with 3 arguments (the user of the bullets position and direction and the type of bullet being fired)
Bullet::Bullet(vector3 userPos, int userDir, int type)
{
	bulletM4 = IDENTITY_M4; // Matrix for bullet movement
	bulletPos = userPos; // Where will this bullet start
	bulletType = type; // What kind of bullet is this
	bulletDir = userDir;
	active = false;
	fired = false;

	switch (bulletType) {
	case 0:
		// Assign bullet details
		bulletM4 = glm::translate(bulletPos);
		break;
	case 1:
		// Assign bullet details
		bulletPos.x = -6.0;
		bulletM4 = glm::translate(-6.0f, 0.0f,bulletPos.z);
		break;
	case 2:
		// Assign bullet details
		bulletM4 = glm::translate(bulletPos);
		break;
	case 3:
		// Assign bullet details
		break;
	default:
		break;
	}
}


// Get method for the matrix
matrix4 Bullet::GetBulletMatrix()
{
	return bulletM4;
}


// Alter bullet behavior depending on bullet type
void Bullet::Disrupted()
{
	switch (bulletType) {
	case 0:
		// Effects on the bullet
		break;
	case 1:
		// Effects on the bullet
		break;
	case 2:
		// Effects on the bullet
		break;
	case 3:
		// Effects on the bullet
		break;
	default:
		break;
	}
}

// Do collision damage based on bullet type
void Bullet::BulletDamage()
{
	switch (bulletType) {
	case 0:
		// Hit resolution of bullet type
		break;
	case 1:
		// Hit resolution of bullet type
		break;
	case 2:
		// Hit resolution of bullet type
		break;
	case 3:
		// Hit resolution of bullet type
		break;
	default:
		break;
	}
}

// Player Bullet moves depending on bullet type
void Bullet::Fire()
{

	switch (bulletType) {
	case 0:
		// Movement of bullet type 0
		bulletPos += movement;
		bulletM4 = glm::translate(bulletM4, movement);

		if (bulletPos.z > 4.5f || bulletPos.z < -4.5f || bulletPos.x > 7.0f || bulletPos.x < -7.0f)
		{
			active = false;
			fired = false;
		} 
		else
		{
			switch (bulletDir) {
			case 0:
				movement = vector3(0.0, 0.0, -0.2);
				break;
			case 1:
				movement = vector3(0.2, 0.0, 0.0);
				break;
			case 2:
				movement = vector3(0.0, 0.0, 0.2);
				break;
			case 3:
				movement = vector3(-0.2, 0.0, 0.0);
				break;
			}
		}
		break;
	case 1:
		// Movement of bullet type 1
		bulletPos += movement;
		bulletM4 = glm::translate(bulletM4, movement);

		if (bulletPos.x > 7.0f)
		{
			active = false;
			fired = false;
		}
		else
		{
			if (fired == true)
			{
				movement = vector3(0.2, 0.0, 0.0);
			}
		}
		break;
	default:
		break;
	}
}


// Enemy Bullet moves depending on bullet type
void Bullet::FireEnemy(vector3 playerPos)
{

	switch (bulletType) {
	case 2:
		// Movement of bullet type  2
		
		// Tracking X
		if (playerPos.x < bulletPos.x + 0.05f && playerPos.x > bulletPos.x - 0.05f)
		{
			// STOP IN X
		}
		else
		{
			if (playerPos.x < bulletPos.x)
			{
				movement = vector3(-0.02f, 0.0f, 0.0f);
				bulletPos += movement;
			}
			else if (playerPos.x > bulletPos.x)
			{
				movement = vector3(0.02f, 0.0f, 0.0f);
				bulletPos += movement;
			}
			bulletM4 = glm::translate(bulletM4, movement);
		}

		// Tracking Z
		if (playerPos.z < bulletPos.z + 0.05f && playerPos.z > bulletPos.z - 0.05f)
		{
			// STOP IN Z
		}
		else
		{
			if (playerPos.z < bulletPos.z)
			{
				movement = vector3(0.0f, 0.0f, -0.02f);
				bulletPos += movement;
			}
			else if (playerPos.z > bulletPos.z)
			{
				movement = vector3(0.0f, 0.0f, 0.02f);
				bulletPos += movement;
			}
			bulletM4 = glm::translate(bulletM4, movement);
		}
		
		


		//std::cout << "TEST: " << bulletPos.x;

		break;
	case 3:
		// Movement of bullet type 3
		break;
	default:
		break;
	}
}

void Bullet::ChangePosition(vector3 change)
{
	if (bulletType == 1)
	{
		bulletPos.z += change.z;
		bulletM4 = glm::translate(bulletM4,change);
	}
}

bool Bullet::GetActiveBullet()
{
	return active;
}

void Bullet::SetActiveBullet(bool isActive)
{
	active = isActive;
}

bool Bullet::GetFired()
{
	return fired;
}

void Bullet::SetFired(bool isFired)
{
	fired = isFired;
}

//Destructor
Bullet::~Bullet()
{
}
