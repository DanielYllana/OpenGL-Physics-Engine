#ifndef CYCLONE_PARTICLE_H
#define CYCLONE_PARTICLE_H

#include "core.h"


namespace cyclone {
	/**
* A particle is the simplest object that can be simulated in the
* physics system.
*/
	class Particle
	{
	protected:
		/**
		* Holds the linear position of the particle in
		* world space.
		*/
		Vector3 position;
		/**
		* Holds the linear velocity of the particle in
		* world space.
		*/
		Vector3 velocity;
		/**
		* Holds the acceleration of the particle. This value
		* can be used to set acceleration due to gravity (its primary
		* use), or any other constant acceleration.
		*/
		Vector3 acceleration;

		/**
		* Holds the amount of damping applied to linear
		* motion. Damping is required to remove energy added
		* through numerical instability in the integrator.
		* */
		real damping;

		/**
		* Holds the inverse of the mass of the particle. It
		* is more useful to hold the inverse mass because
		* integration is simpler, and because in real-time
		* simulation it is more useful to have objects with
		* infinite mass (immovable) than zero mass
		* (completely unstable in numerical simulation).
		* 1/m
		*/
		real inverseMass;


		/**
		 * Holds the accumulated force to be applied at the next
		 * simulation iteration only. This value is zeroed at each
		 * integration step.
		 */
		Vector3 forceAccum;

	public:

		/**
		* There are no data members in the particle class that are
		* created on the heap. So all data storage is handled
		* automatically
		*/


		/**
		* Integrates the particle forward in time by the given amount.
		* This function uses a Newton-Euler integration method, which is a
		* linear approximation to the correct integral. For this reason it
		* may be inaccurate in some cases.
		*/
		void integrate(real duration);


		/**
		 * Clears the forces applied to the particle. This will be
		 * called automatically after each integration step.
		 */
		void clearAccumulator();


		/**
		* Adds the given force to the particle, to be
		* applied at the next iteration only
		*/
		void addForce(const Vector3& force);


		void setMass(const real mass);
		real getMass() const;


		void setInverseMas(const real inverseMass);
		real getInverseMass() const;


		bool hasFinitMass() const;

		
		void setDamping(const real damping);
		real getDamping() const;


		void setPosition(const Vector3& position);
		void setPosition(const real x, const real y, const real z);
		void getPosition(Vector3* position) const;
		Vector3 getPosition() const;


		void setVelocity(const Vector3& velocity);
		void setVelocity(const real x, const real y, const real z);
		void getVelocity(Vector3* velocity) const;
		Vector3 getVelocity() const;


		void setAcceleration(const Vector3& acceleration);
		void setAcceleration(const real x, const real y, const real z);
		void getAcceleration(Vector3* acceleration) const;
		Vector3 getAcceleration() const;





		std::string print(bool pos = true, bool vel = false, bool acc = false)
		{
			std::string str = "";

			if (pos)
			{
				str += "Position (";
				str += position.print();
			}

			if (vel)
			{
				str += "Velocity (";
				str += velocity.print();
			}

			if (acc)
			{
				str += "Acceleration (";
				str += acceleration.print();
			}

			return str;
		}
	};
}



#endif // CYCLONE_BODY_H