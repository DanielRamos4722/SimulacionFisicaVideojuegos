#pragma once

#include "Particle.h"

#include <random>

class ParticleSystem;

class ParticleGenerator
{
public:
	ParticleGenerator(ParticleSystem* pS, float frequency, Vector3D pos, Vector3D dir, float angle, float mass, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f);
	~ParticleGenerator() { pS = nullptr; }
	void update(double t);
	void AddParticle();

protected:
	ParticleSystem* pS;
	float frequency;
	double timeSinceLast;

	Vector3D pos;
	Vector3D dir;
	float avgVel;
	float velVariance;
	float angle;

	Vector3D gravity;

	//Particle attributes
	float mass;
	float damp;
	float lifeSpan;
	float maxDistance;
	Vector4 color;
	PxReal size;
};