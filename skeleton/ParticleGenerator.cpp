#include "ParticleGenerator.h"
#include "Random.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* pS, float frequency, Vector3D pos, float randomRange, Vector3D dir, float angle, float mass, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color, PxReal size)
	: pS(pS), mass(mass), timeSinceLast(0.0f), frequency(frequency), pos(pos), dir(dir.normalized()), avgVel(avgVel), velVariance(velVariance), damp(damp), lifeSpan(lifeSpan), maxDistance(maxDistance), color(color), size(size), gravity({ 0.0f, -9.81f, 0.0f }), randomRange(randomRange)
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
    float newRandom = Random::Uniform(0.0, randomRange);
	float z = Random::Uniform(-1.0f, 1.0f);
	float a = Random::Uniform(0.0f, 2.0f * 3.1416f);
	float r = sqrt(1.0f - z * z);
	Vector3D randomDir = Vector3D(r * cos(a), r * sin(a), z);
    Vector3D realPos = pos + randomDir * newRandom;

    float randomVel = Random::Normal(avgVel, velVariance);

    pS->AddParticle(realPos, dir * randomVel, mass, damp, color, size, lifeSpan, maxDistance);
}
