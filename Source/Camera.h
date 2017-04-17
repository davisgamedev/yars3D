#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera
{
private:
	Camera();
	~Camera();

	vector3 pos;
	vector3 up;

	matrix4 viewMatrix;
	matrix4 projectionMatrix;

	static Camera* instance;

public:
	static Camera* GetInstance() {
		if (instance == nullptr) {
			instance = new Camera();
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

	matrix4 GetView(void);
	matrix4 GetProjection(bool ortho);

	void SetPosition(vector3 position);
	void MoveSideways(float increment);
	void MoveUpDown(float increment);
};

#endif