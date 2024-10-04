#include "health_component.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HealthComponent::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_max_hp"), &HealthComponent::get_max_hp);
	ClassDB::bind_method(D_METHOD("set_max_hp", "p_max_hp"), &HealthComponent::set_max_hp);
	ClassDB::add_property("HealthComponent", PropertyInfo(Variant::INT, "max_hp"), "set_max_hp", "get_max_hp");

    ClassDB::bind_method(D_METHOD("get_hp"), &HealthComponent::get_hp);

    ADD_SIGNAL(MethodInfo("dead"));
    ADD_SIGNAL(MethodInfo("change_health", PropertyInfo(Variant::FLOAT, "current_hp")));
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
    emit_signal("change_health", hp);
}

void HealthComponent::heal(double heal)
{
    hp += heal;
    if (hp > max_hp)
    {
        hp = max_hp;
    }
    emit_signal("change_health", hp);
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

double HealthComponent::get_hp() const
{
    return hp;
}

void HealthComponent::set_hp(const double p_hp)
{
    hp = p_hp;
    emit_signal("change_health", hp);
}
