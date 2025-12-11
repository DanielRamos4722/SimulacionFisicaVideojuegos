#include "SolidSystem.h"

SolidSystem::~SolidSystem()
{
	for (auto box : boxes)
	{
		delete box;
	}
	forceSystem = nullptr;
}

void
SolidSystem::update(double t)
{
	for (auto box : boxes)
	{
		forceSystem->updateSolid(t, box);
	}
}

void
SolidSystem::AddBox(SolidBox* box)
{
	boxes.push_back(box);
}

SolidBox* SolidSystem::getAimedBox(Vector3D cameraPos, Vector3D cameraDir)
{
	float radius = 3.0f;         // radio de precision
	float maxDistance = 400.0f;  // alcance
	SolidBox* closest = nullptr;
	float closestT = maxDistance;

	for (auto* box : boxes)
	{
		PxRigidDynamic* rigid = box->getRigid();
		Vector3D objPos = rigid->getGlobalPose().p;;
		Vector3D camToObj = objPos - cameraPos;

		float t = camToObj.dot(cameraDir);

		if (t <= 0.0f || t > maxDistance)
			continue;

		Vector3D closestPoint = cameraPos + cameraDir * t;

		// Distancia lateral al eje
		float radialDist = (objPos - closestPoint).magnitude();

		if (radialDist < radius && t < closestT)
		{
			closest = box;
			closestT = t;
		}
	}

	return closest;
}
