#include "LevelManager.h"

using namespace physx;

LevelManager::LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene, SolidSystem* solidSystem) : gPhysics(gPhysics), gScene(gScene), solidSystem(solidSystem)
{
    createLimits();
    createBoxes();
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
    createWall({ 0.0f, -10.0f, 0.0f }, { 50.0f, 5.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ 0.0f, 5.0f, 15.0f }, { 50.0f, 15.0f, 5.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ 0.0f, 5.0f, -15.0f }, { 50.0f, 15.0f, 5.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
    createWall({ 0.0f, 20.0f, 0.0f }, { 50.0f, 5.0f, 10.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });
    createWall({ 55.0f, 5.0f, 0.0f }, { 5.0f, 15.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
}
