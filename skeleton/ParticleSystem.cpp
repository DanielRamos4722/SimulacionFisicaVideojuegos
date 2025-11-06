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
			forceSystem->update(t, particle);
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

void ParticleSystem::AddParticleGenerator(float frequency, Vector3D pos, Vector3D dir, float mass, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color, PxReal size)
{
	particleGenerators.emplace_back(new ParticleGenerator(this, frequency, pos, dir, mass, avgVel, velVariance, damp, lifeSpan, maxDistance, color, size));
}

void ParticleSystem::AddParticle(Vector3D pos, Vector3D vel, float mass, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance)
{
	particles.emplace_back(new Particle(pos, vel, mass, damp, color, size, lifeSpan, maxDistance));
}
