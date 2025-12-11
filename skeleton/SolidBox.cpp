#include "SolidBox.h"

SolidBox::SolidBox(PxPhysics* physics, PxScene* scene, const PxVec3& position, const PxVec3& dimensions, float mass, const Vector4& color)
{
    PxTransform transform(position);
    actor = physics->createRigidDynamic(transform);
    PxBoxGeometry boxGeom(dimensions);
    PxMaterial* material = physics->createMaterial(0.5f, 0.4f, 0.0f);

    PxShape* shape = actor->createShape(boxGeom, *material);
    PxRigidBodyExt::updateMassAndInertia(*actor, mass);

    scene->addActor(*actor);

    renderItem = new RenderItem();
    renderItem->shape = shape;
    renderItem->actor = actor;
    renderItem->color = color;
    renderItem->transform = nullptr;

    RegisterRenderItem(renderItem);
}

SolidBox::~SolidBox()
{
    if (renderItem)
    {
        DeregisterRenderItem(renderItem);
        delete renderItem;
        renderItem = nullptr;
    }

    if (actor)
    {
        actor->release();
        actor = nullptr;
    }
}