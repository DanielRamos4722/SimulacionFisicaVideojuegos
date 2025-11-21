#pragma once

#include "SpringForce.h"

class AnchoredSpringForce : public SpringForce
{
public:
	AnchoredSpringForce(double k, double resting, const Vector3D& anchorPos) : SpringForce(k, restingLength, anchorPos) {};
};

