#include "velocity_component.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot {



void VelocityComponent::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("set_direction", "p_direction"), &VelocityComponent::set_direction);
    ClassDB::bind_method(D_METHOD("get_direction"), &VelocityComponent::get_direction);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "direction"), "set_direction", "get_direction");

    ClassDB::bind_method(D_METHOD("set_velocity", "p_velocity"), &VelocityComponent::set_velocity);
    ClassDB::bind_method(D_METHOD("get_velocity"), &VelocityComponent::get_velocity);

    ClassDB::bind_method(D_METHOD("set_max_speed", "p_max_speed"), &VelocityComponent::set_max_speed);
    ClassDB::bind_method(D_METHOD("get_max_speed"), &VelocityComponent::get_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_speed"), "set_max_speed", "get_max_speed");

    ClassDB::bind_method(D_METHOD("set_acceleration", "p_acceleration"), &VelocityComponent::set_acceleration);
    ClassDB::bind_method(D_METHOD("get_acceleration"), &VelocityComponent::get_acceleration);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");


    ClassDB::bind_method(D_METHOD("set_impulse", "p_impulse"), &VelocityComponent::set_impulse);
    ClassDB::bind_method(D_METHOD("move", "delta"), &VelocityComponent::move);
}

VelocityComponent::VelocityComponent() :
    direction(Vector2(0, 0)),
    velocity(Vector2(0, 0)),
    max_speed(0),
    current_speed(0),
    acceleration(0),
    gm(nullptr)
{
}

VelocityComponent::~VelocityComponent() 
{

}

void VelocityComponent::set_impulse(Vector2 p_impulse) 
{
    velocity += p_impulse;
    current_speed = velocity.length();
    direction = velocity.normalized();
}

Vector2 VelocityComponent::move(double delta) 
{
    velocity = velocity.move_toward(direction * max_speed, acceleration * delta);
    current_speed = velocity.length();
    return velocity;
}

// Setters and Getters
void VelocityComponent::set_direction(const Vector2& p_direction) 
{
    direction = p_direction;
}
Vector2 VelocityComponent::get_direction() const 
{
    return direction;
}

void VelocityComponent::set_velocity(const Vector2& p_velocity) 
{
    velocity = p_velocity;
}
Vector2 VelocityComponent::get_velocity() const 
{
    return velocity;
}

void VelocityComponent::set_max_speed(double p_max_speed) 
{
    max_speed = p_max_speed;
}
double VelocityComponent::get_max_speed() const 
{
    return max_speed;
}

void VelocityComponent::set_current_speed(double p_current_speed) 
{
    current_speed = p_current_speed;
}
double VelocityComponent::get_current_speed() const 
{
    return current_speed;
}

void VelocityComponent::set_acceleration(double p_acceleration) 
{
    acceleration = p_acceleration;
}
double VelocityComponent::get_acceleration() const 
{
    return acceleration;
}

}  // namespace godot