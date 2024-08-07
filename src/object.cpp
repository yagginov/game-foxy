#include "object.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GameObject::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &GameObject::_damage);
}

GameObject::GameObject() {
}

GameObject::~GameObject() {
    // Add your cleanup here.
}

void GameObject::_ready() {
    add_to_group("BaseGameObject");

}

void GameObject::_physics_process(double delta) {
    
}


void GameObject::_damage(Vector2 enemy_pos)
{
    //_dead();
}
