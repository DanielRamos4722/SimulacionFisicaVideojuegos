#include "Projectile.h"

Projectile::Projectile(Vector3D pos, Vector3D velR, Vector3D velS, float massR, float damp, Vector4 color, PxReal size)
	: Particle(pos, velS, massS = massR* (pow(velR.magnitude(), 2) / pow(velS.magnitude(), 2)), damp, color, size)
{
	// Equilibramos la influencia de la gravedad al ritmo simulado
	gravityS = gravityR * (pow(velS.magnitude(), 2) / pow(velR.magnitude(), 2));

	acc = { 0.0f, gravityS, 0.0f };
}
