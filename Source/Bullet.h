#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "RE\system\SystemSingleton.h"

using namespace ReEng;

class Bullet
{
private:
	matrix4 bulletM4; // Matrix for bullet
	vector3 bulletPos; // Position Vector
	int bulletDir; // Direction Int
	vector3 movement; //Movement Vector
	int bulletType; // Which bullet is this
	bool active;  // Is the bullet dangerous
	bool fired; // Is the bullet in motion

public:
	Bullet(vector3 userPos, int userDir, int type);
	~Bullet();

	// Methods
	matrix4 GetBulletMatrix(); // Get method for the matrix
	void Disrupted(); // Alter bullet behavior depending on bullet type
	void BulletDamage(); // Do collision damage based on bullet type
	void Fire(); // Bullet activates and moves depending on bullet type
	void FireEnemy(vector3 playerPos);
	void ChangePosition(vector3 change); // Update method for position
	bool GetActiveBullet(); // Get method for active state
	void SetActiveBullet(bool isActive); // Set method for active state
	bool GetFired(); // Get method for fired state
	void SetFired(bool isFired); // Set method for fired state
};

