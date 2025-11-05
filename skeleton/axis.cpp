#include "axis.h"

Axis::Axis()
{
	const Vector3D xAxisPos(10.0f, 0.0f, 0.0f);
	const Vector3D yAxisPos(0.0f, 10.0f, 0.0f);
	const Vector3D zAxisPos(0.0f, 0.0f, 10.0f);
	const Vector3D worldOriginPos(0.0f, 0.0f, 0.0f);

	xAxisItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(xAxisPos), Vector4(1, 0, 0, 1));
	yAxisItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(yAxisPos), Vector4(0, 1, 0, 1));
	zAxisItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(zAxisPos), Vector4(0, 0, 1, 1));
	worldOriginItem = new RenderItem(CreateShape(PxSphereGeometry(2)), new PxTransform(worldOriginPos), Vector4(1, 1, 1, 1));
}

void Axis::derregister()
{
	DeregisterRenderItem(xAxisItem);
	DeregisterRenderItem(yAxisItem);
	DeregisterRenderItem(zAxisItem);
	DeregisterRenderItem(worldOriginItem);
	delete xAxisItem;
	delete yAxisItem;
	delete zAxisItem;
	delete worldOriginItem;
}
