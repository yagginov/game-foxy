#include "hitbox.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Hitbox::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_damage"), &Hitbox::get_damage);
	ClassDB::bind_method(D_METHOD("set_damage", "p_damage"), &Hitbox::set_damage);
	ClassDB::add_property("Hitbox", PropertyInfo(Variant::FLOAT, "damage"), "set_damage", "get_damage");

    ClassDB::bind_method(D_METHOD("get_colliding_box_path"), &Hitbox::get_colliding_box_path);
	ClassDB::bind_method(D_METHOD("set_colliding_box_path", "p_colliding_box_path"), &Hitbox::set_colliding_box_path);
	ClassDB::add_property("Hitbox", PropertyInfo(Variant::NODE_PATH, "colliding_box_path"), "set_colliding_box_path", "get_colliding_box_path");

    ClassDB::bind_method(D_METHOD("turn_on"), &Hitbox::turn_on);
    ClassDB::bind_method(D_METHOD("turn_off"), &Hitbox::turn_off);

    ADD_SIGNAL(MethodInfo("hit", PropertyInfo(Variant::VECTOR2, "target_pos")));
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
    if (has_node(colliding_box_path)) {
        colliding_box = get_node<CollisionPolygon2D>(colliding_box_path); 
    }
}

void Hitbox::hit(Vector2 target_pos)
{
    emit_signal("hit", target_pos);
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
    if (colliding_box)
    {
        colliding_box->set_disabled(false);
    }
}

void Hitbox::turn_off()
{
    if (colliding_box)
    {
        colliding_box->set_disabled(true);
    }
}

void Hitbox::set_colliding_box_path(const NodePath& p_colliding_box_path)
{
    colliding_box_path = p_colliding_box_path;
}
NodePath Hitbox::get_colliding_box_path() const
{
    return colliding_box_path;
}