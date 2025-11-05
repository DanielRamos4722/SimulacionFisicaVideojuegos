#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
	for (auto particleGenerator : particleGenerators)
	{
		delete particleGenerator;
	}
	for (auto particle : particles)
	{
		delete particle;
	}
}

void ParticleSystem::update(double t)
{
	for(auto particleGenerator : particleGenerators)
	{
		particleGenerator->update(t);
	}
	for (auto it = particles.begin(); it != particles.end(); )
	{
		Particle* particle = *it;
		particle->updateTime(t);

		if (particle->checkAlive())
		{
			particle->integrate(t);
			++it;
		}
		else
		{
			delete particle;
			it = particles.erase(it);
		}
	}
}

void ParticleSystem::AddParticleGenerator(float frequency, Vector3D pos, Vector3D dir, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color, PxReal size)
{
	particleGenerators.emplace_back(new ParticleGenerator(this, frequency, pos, dir, avgVel, velVariance, damp, lifeSpan, maxDistance, color, size));
}

void ParticleSystem::AddParticle(Vector3D pos, Vector3D vel, Vector3D acc, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance)
{
	particles.emplace_back(new Particle(pos, vel, acc, damp, color, size, lifeSpan, maxDistance));
}
