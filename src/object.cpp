#include "object.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Object::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &Object::_damage);
}

Object::Object() {
    components = nullptr;
}

Object::~Object() {
    // Add your cleanup here.
}

void Object::_ready() {
    add_to_group("BaseObject");

    components = get_node<ComponentsContainer>("ComponentsContainer");
    if (components)
    {
        components->_ready();
	    components->bind(this);
    }

}

void Object::_physics_process(double delta) {
    
}


void Object::_damage(Vector2 enemy_pos)
{
    //_dead();
}

void Object::_dead()
{
    queue_free();
}