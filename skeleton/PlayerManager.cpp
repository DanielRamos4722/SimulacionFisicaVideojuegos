#include "PlayerManager.h"

using namespace physx;

PlayerManager::PlayerManager(PxPhysics* gPhysics, PxScene* gScene, Camera* camera, Vector3D initPos) : gPhysics(gPhysics), gScene(gScene), mCamera(camera), speed(25.0)
{
    PxVec3 halfExtents(0.4f, 4.0f, 0.4f);
    PxBoxGeometry geometry(halfExtents);

    PxMaterial* material = gPhysics->createMaterial(1.0f, 1.0f, 0.0f);

    PxTransform transform(PxVec3(initPos.getX(), initPos.getY(), initPos.getZ()));

    playerBody = gPhysics->createRigidDynamic(transform);
    playerBody->setMass(0.1f);                 // masa del jugador
    playerBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);

    // Evitar que el jugador se tumbe
    playerBody->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

    PxShape* shape = playerBody->createShape(geometry, *material);

    shape->setFlag(PxShapeFlag::eVISUALIZATION, false);

    gScene->addActor(*playerBody);

    mCamera->setPosition(initPos);
}

void PlayerManager::update(double t)
{
    move();
    updateCamera();
}

void PlayerManager::move()
{
    Vector3D moveDir(0, 0, 0);
    Vector3D forward = mCamera->getDir();
    forward.setY(0);
    forward = forward.normalized();
    Vector3D right = forward.cross(Vector3D(0, 1, 0));

    if (keys['W']) moveDir += forward;
    if (keys['S']) moveDir -= forward;
    if (keys['A']) moveDir -= right;
    if (keys['D']) moveDir += right;

    moveDir = moveDir.normalized() * speed;
    playerBody->setLinearVelocity(Vector3D(moveDir.getX(), 0.0f, moveDir.getZ()));
}

void PlayerManager::processKey(unsigned char key)
{
    currentKey = key;
}

void PlayerManager::updateCamera()
{
    Vector3D pos = playerBody->getGlobalPose().p;
    mCamera->setPosition(pos);
}
