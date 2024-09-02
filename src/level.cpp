#include "level.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "main_character.h"

using namespace godot;

void Level::_bind_methods() 
{

}

Level::Level()
{
    gm = nullptr;
}

Level::~Level() 
{
    // Add your cleanup here.
    
}

void Level::_ready()
{
    gm = GameManager::get_singleton();

    add_child(gm);
}