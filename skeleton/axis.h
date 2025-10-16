#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"
#include "vector3D.h"

using namespace physx;

class Axis
{
private:
	RenderItem* xAxisItem;
	RenderItem* yAxisItem;
	RenderItem* zAxisItem;
	RenderItem* worldOriginItem;

public:
	Axis();
	void derregister();
};

