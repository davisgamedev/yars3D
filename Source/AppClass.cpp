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
	m_pPlayerBoundaries = new PrimitiveClass();

	//Initializing the primitives
	//m_pPlayer->GenerateCube(0.5, REWHITE);
	m_pEnemy->GenerateCube(0.7f, REYELLOW);

	m_pBullet->GenerateCube(0.2f, REBLUE);
	m_pKillBullet->GenerateCube(0.4f, REGREEN);
	m_pTrackingBullet->GenerateCube(0.3f, RERED);
	m_pPlayerBoundaries->GeneratePlane(1.0f, REBLACK);

	m_mPlayerBoundaries = glm::translate(IDENTITY_M4, vector3(-0.125f, -2.0f, -0.6f)) *
		glm::scale(IDENTITY_M4, vector3(21.75f, 1.0f, 13.0f)) *
		glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f));

	// Define player object
	player = Player::GetInstance();
	player->GenerateModel(REWHITE);
	playerPos = vector3(0.0f, 0.0f, 0.0f);

	// define enemy object
	enemy = Enemy::GetInstance();

	// adding our camera
	camera = Camera::GetInstance();

	// add disruptor array reference
	//fieldCubes = new PrimitiveClass*[72];
	fieldCubes = new PrimitiveClass*[numCubes];
	// then do cube creation here
	fieldCubes = GenerateDisruptorField();

	// enemy bullets
	enemy->enemyBullet = new Bullet(enemy->GetPosition(), 3, 3);
	trackingBullet = new Bullet(enemy->GetPosition(), 3, 2);
	trackingBullet->SetActiveBullet(true);

	// Audio Stuff
	String sRoute = m_pSystem->m_pFolder->GetFolderData();
	sRoute += m_pSystem->m_pFolder->GetFolderAudio();

	//Background music
	soundBGM.openFromFile(sRoute + "music1.wav");
	soundBGM.play();
	soundBGM.setLoop(true);

	//sound effect
	soundBuffer.loadFromFile(sRoute + "SpaceGun04.wav");
	sound.setBuffer(soundBuffer);
	//Will be attached to space bar

	frameCount = 0;

	gameState = 0;

	win = false;
	dead = false;
}

void AppClass::Update(void)
{

	//IF IN BEGIN MODE
	if (gameState == 0) {
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("                             Yars Revenge 3D", REYELLOW);
		m_pMeshMngr->PrintLine("");
		m_pMeshMngr->PrintLine("                               Press Enter!", REWHITE);

	} //END BEGIN MODE


	//IF IN GAME MODE
	if (gameState == 1) {

		timer += 1;
		if (timer > 10)
		{
			// change disruptor field colors on a timed basis
			SwitchColors();
			timer = 0;
		}

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

		m_pMeshMngr->Print("Lives: ");
		m_pMeshMngr->PrintLine(std::to_string(player->getPlayerLives()), RERED);

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



		// Check for bullet collisions
			player->DetectCollisions(player->killBullet);
			player->DetectCollisions(enemy->enemyBullet);
			player->DetectCollisions(trackingBullet);
			enemy->DetectEnemyKillShot(player->killBullet);
			enemy->DetectBarrierCollisions(player->killBullet, player);
			enemy->DetectBarrierCollisions(player->mainBullet, player);
			enemy->DetectEnemyCollisions(player);
			if (player->getPlayerLives() <= 0) {
				dead = true;
			}
			if (enemy->getEnemyLives() <= 0) {
				win = true;
			}
		

		//Enemy Bullet Updates
		trackingBullet->FireEnemy(player->GetPlayerPosition());

		if (enemy->GetLaunch() == true)
		{
			enemy->enemyBullet->FireEnemy(player->GetPlayerPosition());
		}
		if (enemy->enemyBullet->GetActiveBullet() == false)
		{
			enemy->EndLaunch();
		}

		//CHECK FOR END STATE
		if (dead == true || win == true) {
			//gameState = 2;
		}

	} //END GAME MODE


	  //IF IN END MODE
	if (gameState == 2) {
		if (dead == true) {
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("                             Yars Revenge 3D", REYELLOW);
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("                                GAME OVER!", RERED);
		} else if (win == true) {
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("                             Yars Revenge 3D", REYELLOW);
			m_pMeshMngr->PrintLine("");
			m_pMeshMngr->PrintLine("                                 YOU WIN!", REBLUE);
		}
	} //END THE END MODE
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	frameCount++;
	//frameCount %= sizeof(int);


	//IF IN GAME MODE
	if (gameState == 1) {

		// render cubes from field cubes array while modifying placement
		vector3 currentLocation = vector3(-3.0f, -1.0f, -7.5f);
		matrix4 disruptorMat = glm::translate(currentLocation);
		matrix4 disRot = glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f)); //for rotating the planes
		for (int i = 0; i < numCubes; i++)
		{
			disruptorMat = glm::translate(currentLocation);

			// if modulus 4, else add one in z and go back to -3 x\
			// if modulus (i+1) [fixes last and first pixel messup] mod (1/sizecubes) [interval of width based on size]
			if ((i + 1) % (4 * (int)(1 / sizeCubes)) == 0)
			{
				currentLocation = vector3(-3.0f, -1.0f, currentLocation.z + sizeCubes);
			}
			else
			{
				currentLocation += vector3(sizeCubes, 0.0f, 0.0f);
			}

			fieldCubes[i]->Render(camera->GetProjection(false), camera->GetView(), disruptorMat * disRot);
		}

		// Get the player Matrix
		matrix4 playerMatrix = player->GetPlayerMatrix();

		// Renders the meshes using the specified position given by the matrix and in the specified color
		//m_pPlayer->Render(camera->GetProjection(false), camera->GetView(), playerMatrix);
		player->Render(camera->GetProjection(false), camera->GetView(), playerMatrix, (frameCount / 4) % 2 == 0);

		// render another cube to represent the enemy
		if (enemy->enemyBullet->GetReturn() == true && enemy->GetFiring() == true)
		{
			enemy->SetFiring(false);
			enemy->enemyBullet->SetReturn(false);
		}
		if (enemy->GetFiring() == true)
		{
			if (enemy->GetLaunch() == false)
			{
				EnemyLaunch();
			}
			m_pEnemy->Render(camera->GetProjection(false), camera->GetView(), enemy->enemyBullet->GetBulletMatrix());
		}
		else if (enemy->GetLaunch() == false)
		{
			m_pEnemy->Render(camera->GetProjection(false), camera->GetView(), enemy->GetMatrix());
		}

		//Display Bullets
		if (player->mainBullet->GetActiveBullet() == true)
		{
			m_pBullet->Render(camera->GetProjection(false), camera->GetView(), player->mainBullet->GetBulletMatrix());
		}

		else if (enemy->GetLaunch() == false)
		{
			m_pEnemy->Render(camera->GetProjection(false), camera->GetView(), enemy->GetMatrix());
		}

		enemy->RenderModel(camera->GetProjection(false), camera->GetView());

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
		m_pPlayerBoundaries->Render(camera->GetProjection(false), camera->GetView(), m_mPlayerBoundaries);
	}//END GAME MODE
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

// creates a list of pointers to primitives for the disruptor field
PrimitiveClass** AppClass::GenerateDisruptorField()
{
	PrimitiveClass** temp = new PrimitiveClass*[numCubes];

	// create the primitives to be used in the disruptor field rendering
	for (int i = 0; i < numCubes; i++)
	{
		// determine color for each block
		vector3 color;
		int num = rand() % 6;

		switch (num)
		{
		case 0: color = REPURPLE;
			break;
		case 1: color = RERED;
			break;
		case 2: color = REBLUE;
			break;
		case 3: color = REGREEN;
			break;
		case 4: color = REORANGE;
			break;
		case 5: color = REYELLOW;
			break;
		}

		PrimitiveClass* block = new PrimitiveClass();
		//block->GenerateCube(1.0, color);
		block->GeneratePlane(sizeCubes, color);
		temp[i] = block;
	}

	return temp;
}

void AppClass::SwitchColors()
{
	for (int i = 0; i < numCubes; i++)
	{
		// determine color for each cube
		int num2 = rand() % numCubes;
		fieldCubes[i]->Swap(*fieldCubes[num2]);
	}
}

void AppClass::EnemyLaunch()
{
	enemy->enemyBullet = new Bullet(enemy->GetPosition(), 3, 3);
	enemy->enemyBullet->ChangePosition(vector3(0.0f, 0.0f, 0.0f), player->GetPlayerPosition());
	enemy->Shoot();
}

void AppClass::Reset() 
{
	m_pEnemy = new PrimitiveClass();

	m_pBullet = new PrimitiveClass();
	m_pKillBullet = new PrimitiveClass();
	m_pTrackingBullet = new PrimitiveClass();
	m_pPlayerBoundaries = new PrimitiveClass();

	//Initializing the primitives
	m_pEnemy->GenerateCube(0.7f, REYELLOW);

	m_pBullet->GenerateCube(0.2f, REBLUE);
	m_pKillBullet->GenerateCube(0.4f, REGREEN);
	m_pTrackingBullet->GenerateCube(0.3f, RERED);
	m_pPlayerBoundaries->GeneratePlane(1.0f, REBLACK);

	m_mPlayerBoundaries = glm::translate(IDENTITY_M4, vector3(-0.125f, -2.0f, -0.6f)) *
		glm::scale(IDENTITY_M4, vector3(21.75f, 1.0f, 13.0f)) *
		glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f));

	// Define player object
	player->Player::ReleaseInstance();
	player->Player::GetInstance();
	player->GenerateModel(REWHITE);
	playerPos = vector3(0.0f, 0.0f, 0.0f);

	// define enemy object
	enemy->Enemy::ReleaseInstance();
	enemy->Enemy::GetInstance();


	// add disruptor array reference
	//fieldCubes = new PrimitiveClass*[72];
	fieldCubes = new PrimitiveClass*[numCubes];
	// then do cube creation here
	fieldCubes = GenerateDisruptorField();

	// enemy bullets
	enemy->enemyBullet = new Bullet(enemy->GetPosition(), 3, 3);
	trackingBullet = new Bullet(enemy->GetPosition(), 3, 2);
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

	gameState = 0;

	win = false;
	dead = false;
}

void AppClass::Release(void)
{
	//SafeDelete(m_pPlayer);
	SafeDelete(m_pEnemy);
	SafeDelete(m_pBullet);
	SafeDelete(m_pKillBullet);
	SafeDelete(m_pTrackingBullet);
	SafeDelete(trackingBullet);
	SafeDelete(m_pPlayerBoundaries);
	delete[] fieldCubes;
	fieldCubes = nullptr;

	player->ReleaseInstance();
	player = nullptr;

	enemy->ReleaseInstance();
	enemy = nullptr;

	camera->ReleaseInstance();
	camera = nullptr;

	soundBGM.stop();
	super::Release(); //release the memory of the inherited fields
}