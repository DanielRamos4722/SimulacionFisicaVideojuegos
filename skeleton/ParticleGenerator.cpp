#include "ParticleGenerator.h"
#include "Random.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* pS, float frequency, Vector3D pos, Vector3D dir, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color, PxReal size)
	: pS(pS), timeSinceLast(0.0f), frequency(frequency), pos(pos), dir(dir.normalize()), avgVel(avgVel), velVariance(velVariance), damp(damp), lifeSpan(lifeSpan), maxDistance(maxDistance), color(color), size(size), gravity({ 0.0f, -9.81f, 0.0f })
{
}

void ParticleGenerator::update(double t)
{
	timeSinceLast += t;
	if (timeSinceLast > frequency)
	{
		timeSinceLast = 0.0f;
		AddParticle();
	}
}

void ParticleGenerator::AddParticle()
{
	float randomVel = Random::Normal(avgVel, velVariance);
	pS->AddParticle(pos, dir * randomVel, gravity, damp, color, size, lifeSpan, maxDistance);
}
