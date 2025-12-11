#include "GunForce.h"

void
GunForce::processForce(double t, SolidBox* box)
{
    PxRigidDynamic* rigid = box->getRigid();
    Vector3D diff = playerT->p - rigid->getGlobalPose().p;
    float distance = diff.magnitude();
    if (distance >= radius) return;

    Vector3D dir = diff.normalized();
    Vector3D vel = rigid->getLinearVelocity();
    float mass = rigid->getMass();

    float proximity = 1.0f - (distance / radius); // 0 en borde exterior, 1 en centro
    float blend = smoothstep(0.2f, 1.6f, proximity); // Suavizar comportamiento entre lejos y cerca

    // Fuerza lejana: Cuanto mas cerca mayor atraccion
    float forceFarMag = farForce * (1.0f - (distance / radius));
    Vector3D forceFar = dir * forceFarMag;

    // Fuerza cercana: Amortiguamos segun llega.
    Vector3D springForce = dir * (nearStiff * mass * distance);
    Vector3D dampingForce = vel * (-damping * mass);
    Vector3D forceNear = springForce + dampingForce;

    // mezclamos de forma suave entre far y near
    Vector3D force = forceFar * (1.0f - blend) + forceNear * blend;

    rigid->addForce(force);
}

void
GunForce::processForce(double t, Particle* particle)
{
    Vector3D diff = playerT->p - particle->getCurrentPos();
    float distance = diff.magnitude();
    if (distance >= radius) return;

    Vector3D dir = diff.normalized();
    Vector3D vel = particle->getCurrentVel();
    float mass = particle->getMass();

    float proximity = 1.0f - (distance / radius); // 0 en borde exterior, 1 en centro
    float blend = smoothstep(0.2f, 1.6f, proximity); // Suavizar comportamiento entre lejos y cerca

    // Fuerza lejana: Cuanto mas cerca mayor atraccion
    float forceFarMag = farForce * (1.0f - (distance / radius));
    Vector3D forceFar = dir * forceFarMag;

    // Fuerza cercana: Amortiguamos segun llega.
    Vector3D springForce = dir * (nearStiff * mass * distance);
    Vector3D dampingForce = vel * (-damping * mass);
    Vector3D forceNear = springForce + dampingForce;

    // mezclamos de forma suave entre far y near
    Vector3D force = forceFar * (1.0f - blend) + forceNear * blend;

    particle->addForce(force);
}
