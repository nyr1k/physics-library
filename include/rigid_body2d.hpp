
#include "math/vector2d.hpp"

namespace phys{

    class RigidBody2D {
        public:
            physm::vec2f position;
            physm::vec2f velocity;
            physm::vec2f accel; 
            physm::vec2f accum_forces;
            float mass; 
            float inv_mass;

            constexpr RigidBody2D() : position{}, velocity{}, accel{}, 
                                        accum_forces{}, mass(0.0f), inv_mass(0.0f) {}

            constexpr RigidBody2D(const physm::vec2f position, 
                                    const physm::vec2f velocity,
                                    const physm::vec2f accel,
                                    const physm::vec2f accum_forces,
                                    const float mass) 
            : position(position), velocity(velocity), accel(accel), 
                accum_forces(accum_forces), mass(mass), inv_mass(1.0f/mass) {}
    };

using rb2 = RigidBody2D;
}