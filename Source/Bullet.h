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
	int bulletType; // Which bullet is this
	bool active;  // Is the bullet dangerous

public:
	Bullet(vector3 userPos, int type);
	~Bullet();

	// Methods
	matrix4 GetBulletMatrix(); // Get method for the matrix
	void Disrupted(); // Alter bullet behavior depending on bullet type
	void BulletDamage(); // Do collision damage based on bullet type
	void Fire(); // Bullet activates and moves depending on bullet type
};

