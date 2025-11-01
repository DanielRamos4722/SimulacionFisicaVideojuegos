#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, Vector4 color, PxReal size) : vel(vel), acc(acc), damp(damp), pose(PxTransform(pos))
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(size)), &pose, color);
	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
	vel += (acc * t);
	vel = vel * pow(damp, t);

}