#include "LevelManager.h"

using namespace physx;

LevelManager::LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene, SolidSystem* solidSystem, ForceSystem* forceSystem, ParticleSystem* particleSystem)
    : gPhysics(gPhysics), gScene(gScene), solidSystem(solidSystem), forceSystem(forceSystem), particleSystem(particleSystem)
{
    createLimits();
    createBoxes();
    createForces();
    createParticles();
}

LevelManager::~LevelManager()
{
    for (RenderItem* item : renderItems)
    {
        DeregisterRenderItem(item);
        delete item;
    }
    renderItems.clear();

    for (PxRigidActor* solid : limits)
    {
        solid->release();
    }
    limits.clear();

    solidSystem = nullptr;
}

void LevelManager::createWall(Vector3D pos, Vector3D halfDimensions, Vector4 color)
{
    PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);

    PxRigidStatic* ground = gPhysics->createRigidStatic(PxTransform(pos));
    PxBoxGeometry geometry(halfDimensions);
    PxShape* shape = ground->createShape(geometry, *material);
    RenderItem* item = new RenderItem(shape, ground, color);

    renderItems.push_back(item);
    limits.push_back(ground);

    RegisterRenderItem(item);
    gScene->addActor(*ground);
}

void LevelManager::createBoxes()
{
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, -3.0f, -7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, -3.0f, -2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, -3.0f, 2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, -3.0f, 7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));

    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 2.0f, -7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 2.0f, -2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 2.0f, 2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 2.0f, 7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));

    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 7.0f, -7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 7.0f, -2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 7.0f, 2.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
    solidSystem->AddBox(new SolidBox(gPhysics, gScene, Vector3D(0.0f, 7.0f, 7.5f), Vector3D(2.0f, 2.0f, 2.0f), 10.0f, Vector4(0.9f, 0.9f, 0.9f, 1.0f)));
}

void LevelManager::createLimits()
{
    //Pasillo inicial
    createWall({ 0.0f, -10.0f, 0.0f }, { 50.0f, 5.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ 0.0f, 5.0f, 20.0f }, { 50.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ 0.0f, 5.0f, -20.0f }, { 50.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ 0.0f, 20.0f, 0.0f }, { 50.0f, 5.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ 55.0f, 5.0f, 0.0f }, { 5.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

    //Sala amplia
    createWall({ -65.0f, -10.0f, 0.0f }, { 15.0f, 5.0f, 30.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -65.0f, 5.0f, 30.0f }, { 15.0f, 15.0f, 5.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -65.0f, 5.0f, -30.0f }, { 15.0f, 15.0f, 5.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -75.0f, 5.0f, -20.0f }, { 5.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -75.0f, 5.0f, 20.0f }, { 5.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -110.0f, 4.0f, 0.0f }, { 30.0f, 1.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -110.0f, -2.0f, 0.0f }, { 30.0f, 5.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -110.0f, 4.0f, 0.0f }, { 30.0f, 1.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });

    //Paredes charcos
    createWall({ -165.0f, 5.0f, 20.0f }, { 85.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -165.0f, 5.0f, -20.0f }, { 85.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

    //Primer charco
    createWall({ -165.0f, 4.0f, 7.0f }, { 10.0f, 1.0f, 3.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -165.0f, -2.0f, 7.0f }, { 10.0f, 5.0f, 3.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -185.0f, 4.0f, 0.0f }, { 10.0f, 1.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -185.0f, -2.0f, 0.0f }, { 10.0f, 5.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

    //Segundo charco
    createWall({ -220.0f, 4.0f, -7.0f }, { 10.0f, 1.0f, 3.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -220.0f, -2.0f, -7.0f }, { 10.0f, 5.0f, 3.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ -240.0f, 4.0f, 0.0f }, { 10.0f, 1.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ -240.0f, -2.0f, 0.0f }, { 10.0f, 5.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
}

void LevelManager::createForces()
{
    forceSystem->addBuoyancyForce(4.0f, 8.0f, 1000.0f, 2.0f);
    forceSystem->addWindForceGenerator(Vector3D(0.0f, 0.0f, -1000.0f), Vector3D(-150.f, 2.0f, 10.0f), 8.0f, 10.0f);
    forceSystem->addWindForceGenerator(Vector3D(0.0f, 0.0f, 1000.0f), Vector3D(-205.f, 2.0f, 10.0f), 8.0f, 10.0f);
}

void LevelManager::createParticles()
{
    particleSystem->AddParticleGenerator(0.2f, { -60.0f, -4.0f, 15.0f }, 0.0f, { 0.0f, 1.0f, 0.0f }, 360.0f, 10.0f, 10.0f, 4.0f, 0.98f, 1.5f, 100.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f), 0.3f);
}