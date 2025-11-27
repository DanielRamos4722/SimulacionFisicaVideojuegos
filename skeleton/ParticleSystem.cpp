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
	particles.emplace_back(new Particle(pos, vel, mass, damp, size, color, lifeSpan, maxDistance));
}

Particle* ParticleSystem::getAimedParticle(Vector3D cameraPos, Vector3D cameraDir)
{
	float radius = 3.0f;         // radio de precision
	float maxDistance = 400.0f;  // alcance
	Particle* closest = nullptr;
	float closestT = maxDistance;

	for (auto* p : particles)
	{
		Vector3D objPos = p->getCurrentPos();
		Vector3D camToObj = objPos - cameraPos;

		float t = camToObj.dot(cameraDir);

		if (t <= 0.0f || t > maxDistance)
			continue;

		Vector3D closestPoint = cameraPos + cameraDir * t;

		// Distancia lateral al eje
		float radialDist = (objPos - closestPoint).magnitude();

		if (radialDist < radius && t < closestT)
		{
			closest = p;
			closestT = t;
		}
	}

	return closest;
}
