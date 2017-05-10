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
	bReturn = false;

	verticalBoundaryTop = 5.0f; // set max/min vertical boundary (z axis)
	verticalBoundaryBottom = 5.75f; // set max/min vertical boundary (z axis)
	horizontalBoundaryLeft = 9.35f; // set max/min horizontal boudnary (x axis)
	horizontalBoundaryRight = 9.15f; // set max/min horizontal boudnary (x axis)

	switch (bulletType) {
	case 0:
		// Assign bullet details
		bulletM4 = glm::translate(bulletPos);
		break;
	case 1:
		// Assign bullet details
		bulletPos.x = -9.35;
		bulletM4 = glm::translate(-9.35f, 0.0f,bulletPos.z);
		break;
	case 2:
		// Assign bullet details
		bulletM4 = glm::translate(bulletPos);
		break;
	case 3:
		// Assign bullet details
		bulletM4 = glm::translate(bulletPos);
		spin = 0;
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

		if (bulletPos.z > 6.0f || bulletPos.z < -6.5f || bulletPos.x > 10.0f || bulletPos.x < -10.0f)
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
				movement = vector3(-0.2, 0.0, 0.0);
				break;
			case 2:
				movement = vector3(0.0, 0.0, 0.2);
				break;
			case 3:
				movement = vector3(0.2, 0.0, 0.0);
				break;
			}
		}
		break;
	case 1:
		// Movement of bullet type 1
		bulletPos += movement;
		bulletM4 = glm::translate(bulletM4, movement);

		if (bulletPos.x > 10.0f)
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
		bulletM4 = glm::rotate(bulletM4, -spin, vector3(0.0f, 1.0f, 0.0f));

		if (bulletPos.z > 7.0f || bulletPos.z < -7.5f || bulletPos.x > 12.0f || bulletPos.x < -12.0f)
		{
			active = false;
			fired = false;
			bReturn = true;
		}
		else
		{
			active = true;
			movement = vector3(-0.3f, 0.0f, 0.0f);
			bulletPos += movement;
			bulletM4 = glm::translate(bulletM4, movement);


				if (right == true)
				{
					if (lDist == true)
					{
						movement = vector3(0.0f, 0.0f, -0.1f);
					}
					else
					{
						movement = vector3(0.0f, 0.0f, -0.05f);
					}
					bulletPos += movement;
					bulletM4 = glm::translate(bulletM4, movement);
				}
				else if (left == true)
				{
					if (lDist == true)
					{
						movement = vector3(0.0f, 0.0f, 0.1f);
					}
					else
					{
						movement = vector3(0.0f, 0.0f, 0.05f);
					}


					bulletPos += movement;
					bulletM4 = glm::translate(bulletM4, movement);

				}

		}
		spin = spin + 10;
		bulletM4 = glm::rotate(bulletM4, spin, vector3(0.0f, 1.0f, 0.0f));
		break;
	default:
		break;
	}
}

void Bullet::ChangePosition(vector3 change, vector3 playerPos)
{
	if (bulletType == 1)
	{
		bulletPos.z += change.z;
		bulletM4 = glm::translate(bulletM4,change);
		WrapBullet();
	}
	else if (bulletType == 3)
	{
		if (playerPos.z < bulletPos.z + 1.0f && playerPos.z > bulletPos.z - 1.0f)
		{
			right = false;
			left = false;
		}
		else if (playerPos.z < bulletPos.z)
		{
			right = true;
			left = false;
			if (bulletPos.z > 0.0f)
			{
				lDist = true;
			}
			else
			{
				lDist = false;
			}
		}
		else if (playerPos.z > bulletPos.z)
		{
			left = true;
			right = false;
			if (bulletPos.z < 0.0f)
			{
				lDist = true;
			}
			else
			{
				lDist = false;
			}
		}
	}
}

void Bullet::WrapBullet() { // Wraps player on vertical axis
	if (bulletType == 1)
	{
		if (bulletPos.z > verticalBoundaryBottom) {
			bulletPos.z = -verticalBoundaryTop;
			bulletM4 = glm::translate(IDENTITY_M4, bulletPos);
		}
		else if (bulletPos.z < -verticalBoundaryTop) {
			bulletPos.z = verticalBoundaryBottom;
			bulletM4 = glm::translate(IDENTITY_M4, bulletPos);
		}
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

bool Bullet::GetReturn()
{
	return bReturn;
}

void Bullet::SetReturn(bool isReturn)
{
	bReturn = isReturn;
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
