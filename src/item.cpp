#include "item.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Item::_bind_methods() {

}

Item::Item() {

}

Item::~Item() {
    // Add your cleanup here.
}

void Item::_ready() {
    add_to_group("Items");
}

void Item::_physics_process(double delta) {
    
}


void Item::use_item()
{
    
}