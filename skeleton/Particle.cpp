#include "Particle.h"

#include <iostream>

Particle::Particle(Vector3D pos, Vector3D vel, float mass, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance)
	: vel(vel), mass(mass), damp(damp), lifeSpan(lifeSpan), maxDistance(maxDistance), pose(new PxTransform(pos)), initPos(pos), aliveTime(0.0f)
{
	PxShape* shape = CreateShape(PxSphereGeometry(size));
	renderItem = new RenderItem(shape, pose, color);

	limitedTime = (lifeSpan != 0.0f);
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
	acc = force / mass;

	pose->p += vel * t;
	vel += (acc * t);
	vel = vel * pow(damp, t);

	force = Vector3D();

}

bool Particle::checkAlive()
{
	return !limitedTime || ((initPos - pose->p).magnitude() < maxDistance) && (aliveTime < lifeSpan);
}

void Particle::setGrabbed()
{
	limitedTime = false;
	maxDistance = 1000.0f;
}
