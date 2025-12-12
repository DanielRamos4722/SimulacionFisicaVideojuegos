#include "ParticleGenerator.h"
#include "Random.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(ParticleSystem* pS, float frequency, Vector3D pos, Vector3D dir, float angle, float mass, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color, PxReal size)
	: pS(pS), mass(mass), timeSinceLast(0.0f), frequency(frequency), pos(pos), dir(dir.normalized()), avgVel(avgVel), velVariance(velVariance), damp(damp), lifeSpan(lifeSpan), maxDistance(maxDistance), color(color), size(size), gravity({ 0.0f, -9.81f, 0.0f })
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
    float cosTheta = cos(angle);
    float z = Random::Uniform(cosTheta, 1.0f);
    float phi = Random::Uniform(0.0f, 2.0f * 3.1416f);
    float r = sqrt(1.0f - z * z);
    Vector3D localDir(r * cos(phi), r * sin(phi), z);

    Vector3D up = fabs(dir.getZ()) < 0.999f ? Vector3D(0, 0, 1) : Vector3D(1, 0, 0);
    Vector3D tangent = dir.cross(up).normalized();
    Vector3D bitangent = dir.cross(tangent);
    Vector3D finalDir = (tangent * localDir.getX() + bitangent * localDir.getY() + dir * localDir.getZ()).normalized();

    pS->AddParticle(pos, finalDir * randomVel, mass, damp, color, size, lifeSpan, maxDistance);
}
