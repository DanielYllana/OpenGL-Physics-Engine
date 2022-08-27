#include <assert.h>
#include "particle.h"

using namespace cyclone;


void Particle::integrate(real duration) 
{
	// We don’t integrate things with infinite mass.
	if (inverseMass <= 0.0f) return;

	assert(duration > 0.0);

	// Update linear position. p' = p + v*t
	// dont use acceleration to simplify
	position.addScaledVector(velocity, duration);

	// Work out the acceleration from the force.
	// (We’ll add to this vector when we come to generate forces.)
	Vector3 resultingAcc = acceleration;

	// Update linear velocity from the acceleration. v' = v + a*t
	velocity.addScaledVector(resultingAcc, duration);

	// Impose drag.
	velocity *= real_pow(damping, duration);

	// Clear the forces.
	clearAccumulator();
}


void Particle::clearAccumulator()
{
	forceAccum.clear();
}



void Particle::addForce(const Vector3& force)
{
	forceAccum += force;
}


void Particle::setMass(const real mass)
{
	assert(mass != 0);
	Particle::inverseMass = ((real)1.0) / mass;
}
real Particle::getMass() const
{
	if (inverseMass == 0) {
		return REAL_MAX;
	}
	return ((real)1.0) / inverseMass;
}


void Particle::setInverseMas(const real inverseMass)
{
	Particle::inverseMass = inverseMass;
}
real Particle::getInverseMass() const {
	return inverseMass;
}


bool Particle::hasFinitMass() const
{
	return inverseMass >= 0.0f;
}


void Particle::setDamping(const real damping) {
	Particle::damping = damping;
}
real Particle::getDamping() const {
	return damping;
}


void Particle::setPosition(const Vector3& position)
{
	Particle::position = position;
}
void Particle::setPosition(const real x, const real y, const real z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
void Particle::getPosition(Vector3* position) const
{
	*position = Particle::position;
}
Vector3 Particle::getPosition() const {
	return position;
}


void Particle::setVelocity(const Vector3& velocity)
{
	Particle::velocity = velocity;
}
void Particle::setVelocity(const real x, const real y, const real z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}
void Particle::getVelocity(Vector3* velocity) const
{
	*velocity = Particle::velocity;
}
Vector3 Particle::getVelocity() const
{
	return velocity;
}


void Particle::setAcceleration(const Vector3& acceleration)
{
	Particle::acceleration = acceleration;
}
void Particle::setAcceleration(const real x, const real y, const real z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}
void Particle::getAcceleration(Vector3* acceleration) const
{
	*acceleration = Particle::acceleration;
}
Vector3 Particle::getAcceleration() const
{
	return acceleration;
}

