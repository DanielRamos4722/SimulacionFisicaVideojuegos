#include "GravityGun.h"

GravityGun::GravityGun(const Camera* camera) : camera(camera), grabbing(false)
{
    pose = new PxTransform(camera->getEye() + camera->getDir() * 8.0f);
    PxShape* gunShape = CreateShape(PxBoxGeometry(2.2f, 0.4f, 0.4f));
    PxShape* crosshairSphere = CreateShape(PxSphereGeometry(0.02f));
    poseGun = new PxTransform();
    updateTransform();
    gun = new RenderItem(gunShape, poseGun, { 1.0f, 0.35f, 0.0f, 1.0f });
    poseCrosshair = new PxTransform(camera->getEye() + camera->getDir() * 2.0f);
    setCrosshair();
    crosshair = new RenderItem(crosshairSphere, poseCrosshair, { 1.0f, 1.0f, 1.0f, 1.0f });

    gunForce = new GunForce(pose, 10.0f, 20.0f, 9.0f, 400.0f);
}

GravityGun::~GravityGun()
{
    DeregisterRenderItem(gun);
    DeregisterRenderItem(crosshair);
    delete gun;
    delete crosshair;
    delete poseGun;
    delete poseCrosshair;
}

void GravityGun::update(double t)
{
    updateTransform();
    setCrosshair();
    if (activeParticle != nullptr)
    {
        gunForce->processForce(t, activeParticle);
    }
}

void GravityGun::updateTransform()
{
    pose->p = camera->getEye() + camera->getDir() * 8.0f;

    Vector3D forward = camera->getDir().getNormalized();
    Vector3D right = forward.cross({ 0.0f, 1.0f, 0.0f }).normalized();
    Vector3D up = right.cross(forward).normalized();

    //Posicionamos el objeto en la esquina de la camara
    Vector3D localOffset(0.9f, -1.4f, 1.0f);
    Vector3D worldPos = camera->getEye() + right * localOffset.getX() + up * localOffset.getY() + forward * localOffset.getZ();

    //Mirar en la direccion a la que apunta la camara unas unidades mas adelante
    Vector3D lookTarget = camera->getEye() + forward * 8.0f;
    Vector3D toTarget = (lookTarget - worldPos).normalized();

    Vector3D xAxis = toTarget;
    Vector3D zAxis = xAxis.cross(up).normalized();
    Vector3D yAxis = zAxis.cross(xAxis).normalized();

    PxMat33 rotation(xAxis, yAxis, zAxis);

    poseGun->p = worldPos;
    poseGun->q = PxQuat(rotation);
    
}

void GravityGun::setCrosshair()
{
    Vector3D pos = camera->getEye() + camera->getDir() * 2.0f;
    poseCrosshair->p = pos;
}

void GravityGun::handleParticle(Particle* particle)
{
    if (!grabbing)
    {
        if (particle != nullptr)
        {
            grabbing = true;
            activeParticle = particle;
            activeParticle->setGrabbed();
            std::cout << particle->getCurrentPos().getX() << " " << particle->getCurrentPos().getY() << " " << particle->getCurrentPos().getZ() << "\n";
        }
    }
    else
    {
        grabbing = false;
        activeParticle = nullptr;
    }
}
