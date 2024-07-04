#include "hitbox.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Hitbox::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_damage"), &Hitbox::get_damage);
	ClassDB::bind_method(D_METHOD("set_damage", "p_damage"), &Hitbox::set_damage);
	ClassDB::add_property("Hitbox", PropertyInfo(Variant::FLOAT, "damage"), "set_damage", "get_damage");

    ClassDB::bind_method(D_METHOD("turn_on"), &Hitbox::turn_on);
    ClassDB::bind_method(D_METHOD("turn_off"), &Hitbox::turn_off);
}

Hitbox::Hitbox()
{
    colliding_box = nullptr;
}

Hitbox::~Hitbox()
{

}

void Hitbox::_ready()
{
    colliding_box = get_node<CollisionShape2D>("CollidingBox");
}

void Hitbox::set_damage(const double p_damage)
{
    damage = p_damage;
}

double Hitbox::get_damage() const
{
    return damage;
}

void Hitbox::turn_on()
{
    colliding_box->set_disabled(false);
}

void Hitbox::turn_off()
{
    colliding_box->set_disabled(true);
}