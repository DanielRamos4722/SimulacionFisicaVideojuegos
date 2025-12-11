#pragma once

#include <vector>
#include "SolidBox.h"
#include "ForceSystem.h"

class SolidSystem
{
public:
	SolidSystem(ForceSystem* forceSystem) : forceSystem(forceSystem) {};
	~SolidSystem();
	void update(double t);
	void AddBox(SolidBox* box);
	SolidBox* getAimedBox(Vector3D cameraPos, Vector3D cameraDir);
private:
	std::vector<SolidBox*> boxes;
	ForceSystem* forceSystem;
};

