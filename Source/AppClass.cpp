#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Yars Revenge 3D");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Sets the camera
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pCube = new PrimitiveClass();

	//Initializing the primitives
	m_pCube->GenerateCube(0.5, REWHITE);

	// Define player object
	player = Player::GetInstance();
	playerPos = vector3(0.0f, 0.0f, 0.0f);

	// adding our camera
	camera = Camera::GetInstance();
}

void AppClass::Update(void)
{
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	playerPos = player->GetPlayerPosition();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine("Yars Revenge 3D", REYELLOW);
	//m_pMeshMngr->Print("FPS:");
	//m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	// Player position, using this to set up player bounderies
	m_pMeshMngr->Print("PlayerPosition: (");
	m_pMeshMngr->Print(std::to_string(playerPos.x), RERED);
	m_pMeshMngr->Print(", ");
	m_pMeshMngr->Print(std::to_string(playerPos.y), RERED);
	m_pMeshMngr->Print(", ");
	m_pMeshMngr->Print(std::to_string(playerPos.z), RERED);
	m_pMeshMngr->PrintLine(")");

	// UI elements
	m_pMeshMngr->PrintLine("Score: ", REYELLOW);
	m_pMeshMngr->PrintLine("Lives: ", REYELLOW);
	
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Matrices from the camera
	//matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	//matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	// Get the player Matrix
	matrix4 playerMatrix = player->GetPlayerMatrix();

	//Renders the meshes using the specified position given by the matrix and in the specified color
	// Render the Cube as the player
	m_pCube->Render(camera->GetProjection(false), camera->GetView(), playerMatrix);
	
	
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_pCube);
	player->ReleaseInstance();
	player = nullptr;

	camera->ReleaseInstance();
	camera = nullptr;

	super::Release(); //release the memory of the inherited fields
}