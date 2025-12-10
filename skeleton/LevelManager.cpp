#include "LevelManager.h"

using namespace physx;

LevelManager::LevelManager(physx::PxPhysics* gPhysics, physx::PxScene* gScene) : gPhysics(gPhysics), gScene(gScene)
{
    createLimits();
}

void LevelManager::createLimits()
{
    PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.1f);
    PxTransform pose(PxVec3(0.0f, -10.0f, 0.0f));
    PxRigidStatic* ground = gPhysics->createRigidStatic(pose);
    PxVec3 halfExtents(50.0f, 5.0f, 20.0f);
    PxBoxGeometry geometry(halfExtents);
    PxShape* shape = ground->createShape(geometry, *material);
    RenderItem* item = new RenderItem(shape, ground, PxVec4(1.0f, 0.0f, 1.0f, 1.0f));
    RegisterRenderItem(item);
    gScene->addActor(*ground);
}
