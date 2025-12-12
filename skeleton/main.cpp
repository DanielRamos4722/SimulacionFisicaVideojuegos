#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "axis.h"

#include "Projectile.h"
#include "ParticleSystem.h"
#include "ForceSystem.h"

#include "SolidSystem.h"
#include "PlayerManager.h"
#include "GravityGun.h"
#include "LevelManager.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//Axis* axis;
std::vector<Projectile*> projectiles;
ForceSystem* forceSystem;
ParticleSystem* particleSystem;

SolidSystem* solidSystem;

PlayerManager* gPlayer;
GravityGun* gravityGun;

LevelManager* levelManager;

void shoot()
{
	Vector3D eye = GetCamera()->getEye();
	Vector3D dir = GetCamera()->getDir();

	Vector3D velR = dir * 100.0f;
	Vector3D velS = dir * 60.0f;


	Projectile* p = new Projectile(eye + (dir * 6.0f), velR, velS, 0.1f, 0.98f);

	projectiles.push_back(p);
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//axis = new Axis();

	forceSystem = new ForceSystem();

	particleSystem = new ParticleSystem(forceSystem);
	solidSystem = new SolidSystem(forceSystem);

	gPlayer = new PlayerManager(gPhysics, gScene, GetCamera(), Vector3D(45.0f, -5.0f, 0.0f));
	gravityGun = new GravityGun(GetCamera());

	levelManager = new LevelManager(gPhysics, gScene, solidSystem, forceSystem, particleSystem);

	gScene->setGravity(Vector3D(0.0f, -20.81f, 0.0f));
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	for (auto projectile : projectiles) {
		projectile->integrate(t);
	}
	forceSystem->update(t);
	particleSystem->update(t);
	solidSystem->update(t);
	gPlayer->update(t);
	gravityGun->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	//axis->derregister();
	for (auto projectile : projectiles) {
		delete projectile;
	}
	delete gPlayer;
	delete levelManager;
	delete solidSystem;
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

void handleMouse(int button, int state)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gravityGun->shoot();
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gravityGun->handleSolid(solidSystem->getAimedBox(GetCamera()->getEye(), GetCamera()->getDir()));
		gravityGun->handleParticle(particleSystem->getAimedParticle(GetCamera()->getEye(), GetCamera()->getDir()));
	}
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	gPlayer->processKey(toupper(key));
	/*switch (toupper(key))
	{
	default:
		break;
	}*/
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}