#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	vector3 pos;
	vector3 up;

	matrix4 viewMatrix;
	matrix4 projectionMatrix;

	matrix4 GetView(void);
	matrix4 GetProjection(bool ortho);

	void SetPosition(vector3 position);
	void MoveSideways(float increment);
	void MoveUpDown(float increment);
};

#endif