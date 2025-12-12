#include "PlayerManager.h"

using namespace physx;

PlayerManager::PlayerManager(PxPhysics* gPhysics, PxScene* gScene, Camera* camera, Vector3D initPos) : gPhysics(gPhysics), gScene(gScene), mCamera(camera), speed(25.0f), jumpForce(1.5f) //1.5
{
    PxVec3 halfExtents(0.4f, 4.0f, 0.4f);
    PxBoxGeometry geometry(halfExtents);

    PxMaterial* material = gPhysics->createMaterial(1.0f, 1.0f, 0.0f);

    PxTransform transform(PxVec3(initPos.getX(), initPos.getY(), initPos.getZ()));

    playerBody = gPhysics->createRigidDynamic(transform);
    playerBody->setMass(0.1f);
    playerBody->setLinearDamping(0.0f);
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

    if (keys[' '] && grounded())
    {
        playerBody->addForce(Vector3D(0.0f, 1.0, 0.0f) * jumpForce, PxForceMode::eIMPULSE);
        keys[' '] = false;
    }
    if (grounded())
    {
        moveDir = moveDir.normalized() * speed;
    }
    else
    {
        moveDir = moveDir.normalized() * (speed / 3.0f);
    }
    playerBody->setLinearVelocity(Vector3D(moveDir.getX(), playerBody->getLinearVelocity().y, moveDir.getZ()));
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

bool PlayerManager::grounded()
{
    PxVec3 origin = playerBody->getGlobalPose().p;
    origin.y -= 4.1f;

    PxVec3 direction = PxVec3(0, -1, 0);
    float maxDistance = 0.1f;

    PxRaycastBuffer hit;
    bool grounded = gScene->raycast(origin, direction, maxDistance, hit);

    return grounded;
}
