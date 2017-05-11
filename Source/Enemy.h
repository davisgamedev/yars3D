#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include "Player.h"

class Enemy
{
private:
	// enemy position and orientation for transformations
	matrix4 enemyMatrix;
	vector3 enemyPos;
	bool active;
	int counter; // change movement direction based on the value of this counter
	int counterFire; // decides when to shoot self at player
	bool direction; // either a 0 or 1 to represent current movement direction
	bool firing; // whether or not the enemy is in firing mode (loading up a bullet to shoot, maybe represented by a spinning cube?)
	bool launched; // when the enemy actually shoots itself
	int fireTiming; // when to fire itself
	float spin; // angle of rotation before launching
	int enemyLives;

	static Enemy* instance;

	float enemyLength;

	PrimitiveClass* voxelList = nullptr;
	const int NUM_VOXELS = 64;
	const float SIZE_VOXELS = 0.5f;
	static const int BARRIER_H = 14;
	static const int BARRIER_W = 8;
	const vector3 BARRIER_COMP = vector3(7.0f * SIZE_VOXELS, 0.0f, 6.5f * SIZE_VOXELS);
	const bool BARRIER_REF[BARRIER_H][BARRIER_W] = {
		{ 0, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 0, 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 1, 1, 1 }
	};
	bool barrierVals[BARRIER_H][BARRIER_W];
	bool* renderVoxels = new bool[NUM_VOXELS];
public:
	static Enemy* GetInstance() {
		if (instance == nullptr) {
			instance = new Enemy();
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
	Bullet* enemyBullet = nullptr;
	vector3 GetPosition();
	bool GetFiring();
	void SetFiring(bool setFire);
	bool GetLaunch();
	void EndLaunch();
	void Shoot();
	void Reset();
	void GenerateModel(vector3 color);
	void RenderModel(matrix4 projection, matrix4 view);
	void DetectBarrierCollisions(Bullet* playerBullet, Player* player);
	void DetectEnemyCollisions(Player* player);
	void DetectEnemyKillShot(Bullet* bullet);
	vector3 GetVoxelPosition(int r, int c);

	Enemy();
	~Enemy();

	// move enemy from "side to side" during gameplay (back and forth along axis)
	void Move();

	matrix4 GetMatrix();

	int getEnemyLives();
};

