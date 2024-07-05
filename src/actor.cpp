#include "actor.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;


void Actor::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_index"), &Actor::get_index);
	ClassDB::bind_method(D_METHOD("set_index", "p_index"), &Actor::set_index);
	ClassDB::add_property("Actor", PropertyInfo(Variant::INT, "index"), "set_index", "get_index");

    ClassDB::bind_method(D_METHOD("get_speed"), &Actor::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Actor::set_speed);
	ClassDB::add_property("Actor", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_acceleration"), &Actor::get_acceleration);
	ClassDB::bind_method(D_METHOD("set_acceleration", "p_acceleration"), &Actor::set_acceleration);
	ClassDB::add_property("Actor", PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");

    ADD_SIGNAL(MethodInfo("dead", PropertyInfo(Variant::INT, "index")));
}


Actor::Actor() 
{
	// Initialize any variables here.
    speed = 200;
    acceleration = 200;
    velocity = Vector2(0.0, 0.0);
}

Actor::~Actor() 
{
	// Add your cleanup here.
}

void Actor::_ready() 
{

}

void Actor::move(const Vector2& direction, double delta)
{
    velocity = get_velocity();

    velocity = velocity.move_toward(direction * speed, acceleration * delta);

    set_velocity(velocity);

    move_and_slide();
}

void Actor::set_index(const int p_index)
{
    index = p_index;
}
int Actor::get_index() const
{
    return index;
}
    

void Actor::set_speed(const double p_speed)
{
    speed = p_speed;
}

double Actor::get_speed() const
{
    return speed;
}


void Actor::set_acceleration(const double p_acceleration)
{
    acceleration = p_acceleration;
}

double Actor::get_acceleration() const
{
    return acceleration;
}
