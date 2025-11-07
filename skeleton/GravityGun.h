#pragma once

#include "GunForce.h"

class GravityGun
{
public:
	GravityGun(const Camera* camera);
	~GravityGun();
	void update(double t);
	void updateTransform();
	void setCrosshair();
	void handleParticle(Particle* particle);

private:
	const Camera* camera;
	PxTransform* pose;
	PxTransform* poseGun;
	RenderItem* gun;
	PxTransform* poseCrosshair;
	RenderItem* crosshair;
	bool grabbing;

	GunForce* gunForce;
	Particle* activeParticle = nullptr;
};

