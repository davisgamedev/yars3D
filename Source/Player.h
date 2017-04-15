#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "RE\system\SystemSingleton.h"
using namespace ReEng;

// Player Class
class Player
{
private:
	// Attributes
	matrix4 playerMat; // Matrix for all player transformations
	vector3 playerPos; // vec3 for player position

public:
	// Constructor, Destructor
	Player();
	~Player();

	// Methods
	matrix4 GetPlayerMatrix();
	void MoveVertical(float fIncrement); // Move the player up and down
	void MoveHorizontal(float fIncrement); // Move the left and right
	void Shoot(); // Shoot bullet
};

