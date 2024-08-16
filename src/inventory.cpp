#include "inventory.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Inventory::_bind_methods() 
{

}

Inventory::Inventory() 
{
    gm = nullptr;
}

Inventory::~Inventory() 
{
    // Add your cleanup here.
}

void Inventory::_ready() 
{
    add_to_group("UI");

    gm = GameManager::get_singleton();
}

void Inventory::_physics_process(double delta) 
{
    
}

