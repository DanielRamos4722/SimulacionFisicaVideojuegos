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
    Vector3D realPos = pos + Vector3D(Random::Uniform(-1.0f, 1.0f), Random::Uniform(-1.0f, 1.0f), Random::Uniform(-1.0f, 1.0f)).normalized() * newRandom;

    float randomVel = Random::Normal(avgVel, velVariance);

    float z = Random::Uniform(cos(angle * 3.1416f / 180.0f), 1.0f);
    float r = sqrt(1.0f - z * z);
    float phi = Random::Uniform(0.0f, 2.0f * 3.14159265f);
    Vector3D localDir(r * cos(phi), r * sin(phi), z);
    Vector3D finalDir = (dir + localDir).normalized();

    pS->AddParticle(realPos, finalDir * randomVel, mass, damp, color, size, lifeSpan, maxDistance);
}
