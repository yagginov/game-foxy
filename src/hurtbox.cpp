#include "hurtbox.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Hurtbox::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_health"), &Hurtbox::get_health);
	ClassDB::bind_method(D_METHOD("set_health", "p_health"), &Hurtbox::set_health);
	ClassDB::add_property("Hurtbox", PropertyInfo(Variant::NODE_PATH, "health"), "set_health", "get_health");

    ClassDB::bind_method(D_METHOD("_hitbox_entered"), &Hurtbox::_hitbox_entered);

    ADD_SIGNAL(MethodInfo("damage", PropertyInfo(Variant::VECTOR2, "enemy_pos")));
}

Hurtbox::Hurtbox()
{
    health = nullptr;
}

Hurtbox::~Hurtbox()
{

}

void Hurtbox::_ready()
{
    if (has_node(health_path)) {
        health = get_node<HealthComponent>(health_path);
    }

    this->connect("area_entered", Callable(this, "_hitbox_entered"));
}

void Hurtbox::_hitbox_entered(Hitbox* node)
{
    health->damage(node->get_damage());

    emit_signal("damage", node->get_position());
}

void Hurtbox::set_health(const NodePath& p_health)
{
    health_path = p_health;
}

NodePath Hurtbox::get_health() const
{
    return health_path;
}