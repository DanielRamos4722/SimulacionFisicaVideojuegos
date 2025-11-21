#pragma once

#include "ForceGenerator.h"

class SpringForce : public ForceGenerator
{
public:
	SpringForce(double k, double restingLength, Particle* other) : k(k), restingLength(restingLength), other(other) {};
	SpringForce(double k, double restingLength, const Vector3D& anchorPos);
	void processForce(double t, Particle* particle) override;
	inline void setK(double k) { this->k = k; };
	~SpringForce() { delete other; };
protected:
	double k;
	double restingLength;
	Particle* other;
};

