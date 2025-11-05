#include "Particle.h"

#include <iostream>

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance)
	: vel(vel), acc(acc), damp(damp), lifeSpan(lifeSpan), maxDistance(maxDistance), pose(new PxTransform(pos)), initPos(pos), aliveTime(0.0f)
{
	PxShape* shape = CreateShape(PxSphereGeometry(size));
	renderItem = new RenderItem(shape, pose, color);
}

Particle::~Particle()
{
	if (renderItem)
	{
		DeregisterRenderItem(renderItem);
		delete renderItem;
		delete pose;

	}
}

void Particle::updateTime(double t)
{
	aliveTime += t;
}

void Particle::integrate(double t)
{
	pose->p += vel * t;
	vel += (acc * t);
	vel = vel * pow(damp, t);

}

bool Particle::checkAlive()
{
	return ((initPos - pose->p).magnitude() < maxDistance) && (aliveTime < lifeSpan);
}
