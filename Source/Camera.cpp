#include "Camera.h"
#include "AppClass.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
{
	// give camera a default position - change y value to alter distance from the scene and thus fov
	pos = vector3(0.0f, 10.0f, 0.0f);

	up = vector3(0.0f, 0.0f, -1.0f);
	viewMatrix = glm::lookAt(pos, vector3(0.0f, 0.0f, 0.0f), up);
	projectionMatrix = IDENTITY_M4;
}

matrix4 Camera::GetView(void)
{
	return viewMatrix;
}

matrix4 Camera::GetProjection(bool ortho)
{
	if (ortho == true)
	{
		projectionMatrix = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	}
	else
	{
		projectionMatrix = glm::perspective(45.0f, 4.0f/2.5f, .01f, 1000.0f);
	}

	return projectionMatrix;
}

// can be used to set the position of the camera
void Camera::SetPosition(vector3 position)
{
	pos = position;
	viewMatrix = glm::lookAt(pos, vector3(pos.x, 0.0f, pos.z), up);
}

// this would be moving the camera on the x axis in world view
void Camera::MoveSideways(float increment)
{
	// in case we want to pan the view left/right
}

// would be moving the camera on the z axis in world view
void Camera::MoveUpDown(float increment)
{
	// in case we want to pan the view up/down
}



Camera::~Camera()
{
}
