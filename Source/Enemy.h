#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Enemy
{
private:
	// enemy position and orientation for transformations
	matrix4 enemyMatrix;
	vector3 enemyPos;
	bool active;
	int counter; // change movement direction based on the value of this counter
	bool direction; // either a 0 or 1 to represent current movement direction
	bool firing; // whether or not the enemy is in firing mode (loading up a bullet to shoot, maybe represented by a spinning cube?)
public:
	Enemy();
	~Enemy();

	// move enemy from "side to side" during gameplay (back and forth along axis)
	void Move();

	matrix4 GetMatrix();
};

