#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

using namespace physx;

class SolidBox
{
public:
    SolidBox(PxPhysics* physics, PxScene* scene, const PxVec3& position, const PxVec3& dimensions, float mass, const Vector4& color);
    ~SolidBox();

    PxRigidDynamic* getRigid() const { return actor; }
    RenderItem* getRenderItem() const { return renderItem; }

private:
    PxRigidDynamic* actor = nullptr;
    RenderItem* renderItem = nullptr;
};