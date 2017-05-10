#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "RE\system\SystemSingleton.h"
#include "Bullet.h"
using namespace ReEng;

// Player Class
class Player
{
private:
	// Attributes
	matrix4 playerMat; // Matrix for all player transformations
	vector3 playerPos; // vec3 for player position

	int playerDir; // Int for direction of the player -- 0: Up, 1: Right, 2: Down, 3: Left
	int prevPlayerDir;
	matrix4 rotationMat;

	// keep track of if player is in disruptor field
	bool inField;

	// Player boudaries
	float verticalBoundaryTop;
	float verticalBoundaryBottom;
	float horizontalBoundaryLeft;
	float horizontalBoundaryRight;

	//voxels
	//handle array allocation in Generate
	//handle deletion in class deconstructor
	PrimitiveClass* voxelList = nullptr;
	const int NUM_VOXELS = 26;
	const float SIZE_VOXELS = 0.08f;
	matrix4 voxelMatrixList1[26] = {
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(2.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(3.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 2.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 3.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 3.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 3.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(2.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(3.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 2.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 3.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 3.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 3.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS))
	};
	matrix4 voxelMatrixList2[26] = {
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(2.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(3.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 2.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 2.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 2.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 3.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 0.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 1.5f * SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(1.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(2.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(3.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(0.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-0.5f * SIZE_VOXELS, 0.0f, 2.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 2.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 2.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 3.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-1.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-2.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 0.5f * -SIZE_VOXELS)),
		glm::translate(IDENTITY_M4, vector3(-3.5f * SIZE_VOXELS, 0.0f, 1.5f * -SIZE_VOXELS))
	};

	// Constructor, Destructor
	Player();
	~Player();

	static Player* instance;

public:
	static Player* GetInstance() {
		if (instance == nullptr) {
			instance = new Player();
		}
		return instance;
	}

	static void ReleaseInstance() {
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	// Bullet objects
	Bullet* mainBullet;
	Bullet* killBullet;

	// Methods
	matrix4 GetPlayerMatrix();
	void MoveVertical(float fIncrement); // Move the player up and down
	void MoveHorizontal(float fIncrement); // Move the left and right
	void Shoot(); // Shoot bullet
	vector3 GetPlayerPosition(); // Get the player's position
	int GetPlayerDirection(); // Get the player's direction
	void SetPlayerDirection(int dir); // Sets the player's direction
	int GetPrevPlayerDirection(); // Get the player's direction
	void SetPrevPlayerDirection(int prevDir); // Sets the player's direction
	void WrapPlayer();
	void GenerateModel(vector3 color);
	void Render(matrix4 projection, matrix4 view, matrix4 world, bool movingFrame);
	void setInFieldBool(bool inFld);
	bool getInFieldBool();
	bool Moving = false;
};


