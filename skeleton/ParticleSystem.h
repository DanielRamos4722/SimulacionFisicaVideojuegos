#pragma once

#include <vector>
#include "ParticleGenerator.h"

class ParticleSystem
{
public:
	ParticleSystem() {};
	~ParticleSystem();
	void update(double t);
	void AddParticleGenerator(float frequency, Vector3D pos, Vector3D dir, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f);
	void AddParticle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance);
private:
	std::vector<ParticleGenerator*> particleGenerators;
	std::vector<Particle*> particles;
};