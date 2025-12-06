#pragma once

#include <vector>
#include "ParticleGenerator.h"
#include "ForceSystem.h"

class ParticleSystem
{
public:
	ParticleSystem(ForceSystem* forceSystem) { this->forceSystem = forceSystem; };
	~ParticleSystem();
	void update(double t);
	void AddParticleGenerator(float frequency, Vector3D pos, Vector3D dir, float mass, float avgVel, float velVariance, float damp, double lifeSpan, float maxDistance, Vector4 color = { 1.0f, 0.0f, 0.0f, 1.0f }, PxReal size = 2.0f);
	void AddParticle(Vector3D pos, Vector3D vel, float mass, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance);
	void AddParticle(Particle* particle);
	void AddSpringParticles(Particle* springParticle, Particle* springOther);
	void AddAnchoredSpringParticle(Vector3D pos, Vector3D vel, float mass, float damp, Vector4 color, PxReal size, double lifeSpan, float maxDistance);
	Particle* getAimedParticle(Vector3D cameraPos, Vector3D cameraDir);
private:
	std::vector<ParticleGenerator*> particleGenerators;
	std::vector<Particle*> particles;
	std::vector<Particle*> anchoredSpringParticles;
	std::vector<std::pair<Particle*, Particle*>> springParticles;
	ForceSystem* forceSystem;
};