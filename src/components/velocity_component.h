#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/vector2.hpp>


#include "game_manager.h" 

namespace godot {

class VelocityComponent : public Resource 
{
    GDCLASS(VelocityComponent, Resource);

protected:
    static void _bind_methods();

private:
    Vector2 direction;
    Vector2 velocity;
    double max_speed;
    double current_speed;
    double acceleration;

    GameManager* gm;

public:
    VelocityComponent();
    ~VelocityComponent();

    void set_impulse(Vector2 p_impulse);
    Vector2 move(double delta);


    //  set / get
    void set_direction(const Vector2& p_direction);
    Vector2 get_direction() const;

    void set_velocity(const Vector2& p_velocity);
    Vector2 get_velocity() const;

    void set_max_speed(double p_max_speed);
    double get_max_speed() const;

    void set_current_speed(double p_current_speed);
    double get_current_speed() const;

    void set_acceleration(double p_acceleration);
    double get_acceleration() const;

};

}           // namespace godot

#endif      // VELOCITY_COMPONENT_H
