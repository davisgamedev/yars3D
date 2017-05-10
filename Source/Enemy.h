#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Bullet.h"

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
	
	static Enemy* instance;
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

	Enemy();
	~Enemy();

	// move enemy from "side to side" during gameplay (back and forth along axis)
	void Move();

	matrix4 GetMatrix();
};

