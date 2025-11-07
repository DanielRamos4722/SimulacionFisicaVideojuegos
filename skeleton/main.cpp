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

#include "GravityGun.h"

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

Axis* axis;
std::vector<Projectile*> projectiles;
ForceSystem* forceSystem;
ParticleSystem* particleSystem;

GravityGun* gravityGun;

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

	axis = new Axis();

	forceSystem = new ForceSystem();
	forceSystem->addGravityForceGenerator({0.0f, -9.81f, 0.0f});
	//forceSystem->addWindForceGenerator({-30.0f, 0.0f, 30.0f}, 0.8f);
	forceSystem->addWhirlwindForceGenerator(0.8f, 0.0f, { -55.0f, 15.0f, -55.0f }, -700.0f, 50.0f);
	forceSystem->addExplosionForceGenerator({ 15.0f, 15.0f, 15.0f }, 50000.0f, 200.0f, 10.0f);
	particleSystem = new ParticleSystem(forceSystem);
	particleSystem->AddParticleGenerator(0.2f, { 25.0f, 20.0f, 10.0f }, { -1.0f, 0.0f, 0.0f }, 1.0f, 50.0f, 10.0f, 0.98f, 3.0f, 1000.0f, { 1.0f, 0.0f, 0.0f, 1.0f }, 2.0f);
	particleSystem->AddParticleGenerator(0.2f, { 10.0f, 15.0f, 25.0f }, { 0.0f, 0.0f, -1.0f }, 5.0f, 80.0f, 15.0f, 0.98f, 3.0f, 1000.0f, { 0.0f, 1.0f, 0.0f, 1.0f }, 3.0f);
	particleSystem->AddParticleGenerator(0.1f, { 10.0f, 10.0f, 10.0f }, { -1.0f, 0.0f, -1.0f }, 5.0f, 300.0f, 15.0f, 0.98f, 3.0f, 1000.0f, { 1.0f, 1.0f, 0.0f, 1.0f }, 2.5f);

	gravityGun = new GravityGun(GetCamera());
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
	particleSystem->update(t);

	gravityGun->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	axis->derregister();
	for (auto projectile : projectiles) {
		delete projectile;
	}

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

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'G': grab/let go;
	//case 'H': shoot;
	//case ' ':	break;
	case 'G':
		gravityGun->handleParticle(particleSystem->getAimedParticle(GetCamera()->getEye(), GetCamera()->getDir()));
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
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