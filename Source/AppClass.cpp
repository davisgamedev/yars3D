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

	//m_pPlayer = new PrimitiveClass();
	m_pEnemy = new PrimitiveClass();

	m_pBullet = new PrimitiveClass();
	m_pKillBullet = new PrimitiveClass();
	m_pTrackingBullet = new PrimitiveClass();

	//Initializing the primitives
	//m_pPlayer->GenerateCube(0.5, REWHITE);
	m_pEnemy->GenerateCube(0.7, REYELLOW);

	m_pBullet->GenerateCube(0.2, REBLUE);
	m_pKillBullet->GenerateCube(0.4, REGREEN);
	m_pTrackingBullet->GenerateCube(0.3, RERED);

	// Define player object
	player = Player::GetInstance();
	player->GenerateModel(REWHITE);
	playerPos = vector3(0.0f, 0.0f, 0.0f);

	// define enemy object
	enemy = Enemy::GetInstance();

	// adding our camera
	camera = Camera::GetInstance();

	// TEMP enemy bullet
	trackingBullet = new Bullet(vector3(6.0f, 0.0f, 2.5f), 3, 2);
	trackingBullet->SetActiveBullet(true);

	// Audio Stuff
	String sRoute = m_pSystem->m_pFolder->GetFolderData();
	sRoute += m_pSystem->m_pFolder->GetFolderAudio();

	//Background music
	soundBGM.openFromFile(sRoute + "elementary-wave-11.ogg");
	soundBGM.play();
	soundBGM.setLoop(true);

	//sound effect
	soundBuffer.loadFromFile(sRoute + "SpaceGun04.wav");
	sound.setBuffer(soundBuffer);
	//Will be attached to space bar

	frameCount = 0;
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
	m_pMeshMngr->Print("Current Frame: ", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(frameCount), RERED);

	m_pMeshMngr->Print("PlayerDirection: ");
	m_pMeshMngr->PrintLine(std::to_string(player->GetPlayerDirection()), RERED);

	// update the enemy position
	enemy->Move();

	// UI elements
	m_pMeshMngr->PrintLine("Score: ", REYELLOW);
	m_pMeshMngr->PrintLine("Lives: ", REYELLOW);
	
	//Update bullet positions
	if (player->mainBullet->GetFired() == true)
	{
		player->mainBullet->Fire();
	}
	if (player->killBullet->GetFired() == true)
	{
		player->killBullet->Fire();
	}

	//Enemy Bullet Update
	trackingBullet->FireEnemy(player->GetPlayerPosition());
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	frameCount++;
	//frameCount %= sizeof(int);
	
	//Matrices from the camera
	//matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	//matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	// Get the player Matrix
	matrix4 playerMatrix = player->GetPlayerMatrix();

	//Renders the meshes using the specified position given by the matrix and in the specified color
	// Render the Cube as the player
	//m_pPlayer->Render(camera->GetProjection(false), camera->GetView(), playerMatrix);
	player->Render(camera->GetProjection(false), camera->GetView(), playerMatrix, (frameCount/4)%2==0);

	// render another cube to represent the enemy
	m_pEnemy->Render(camera->GetProjection(false), camera->GetView(), enemy->GetMatrix());

	//Display Bullets
	if (player->mainBullet->GetActiveBullet() == true)
	{
		m_pBullet->Render(camera->GetProjection(false), camera->GetView(), player->mainBullet->GetBulletMatrix());
	}

	if (player->killBullet->GetActiveBullet() == true)
	{
		m_pKillBullet->Render(camera->GetProjection(false), camera->GetView(), player->killBullet->GetBulletMatrix());
	}

	if (trackingBullet->GetActiveBullet() == true)
	{
		m_pTrackingBullet->Render(camera->GetProjection(false), camera->GetView(), trackingBullet->GetBulletMatrix());
	}
	
	
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//SafeDelete(m_pPlayer);
	SafeDelete(m_pEnemy);
	SafeDelete(m_pBullet);
	SafeDelete(m_pKillBullet);
	SafeDelete(m_pTrackingBullet);
	SafeDelete(trackingBullet); //TEMP
	
	player->ReleaseInstance();
	player = nullptr;

	enemy->ReleaseInstance();
	enemy = nullptr;

	camera->ReleaseInstance();
	camera = nullptr;

	soundBGM.stop();
	super::Release(); //release the memory of the inherited fields
}