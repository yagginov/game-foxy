#include "health_component.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HealthComponent::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_max_hp"), &HealthComponent::get_max_hp);
	ClassDB::bind_method(D_METHOD("set_max_hp", "p_max_hp"), &HealthComponent::set_max_hp);
	ClassDB::add_property("HealthComponent", PropertyInfo(Variant::INT, "max_hp"), "set_max_hp", "get_max_hp");

    ADD_SIGNAL(MethodInfo("dead"));
}

HealthComponent::HealthComponent()
{
    max_hp = 3;
    hp = max_hp;
}

HealthComponent::~HealthComponent()
{

}

void HealthComponent::_ready()
{

}

void HealthComponent::_process(double delta)
{
    
}

void HealthComponent::damage(double damage)
{
    hp -= damage;

    if (hp <= 0)
    {
        hp = 0;
        emit_signal("dead");
    }
}

void HealthComponent::heal(double heal)
{

    damage(-heal);
    if (hp > max_hp)
    {
        hp = max_hp;
    }
}


void HealthComponent::set_max_hp(const double p_max_hp)
{
    max_hp = p_max_hp;
    hp = p_max_hp;
}
double HealthComponent::get_max_hp() const
{
    return max_hp;
}
