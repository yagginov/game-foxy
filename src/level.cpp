#include "level.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "main_character.h"

#include <iostream>

using namespace godot;

void Level::_bind_methods() 
{

}

Level::Level()
{
    gm = nullptr;
    std::cout << "Construct Level" << std::endl;
}

Level::~Level() 
{
    // Add your cleanup here.
    
}

void Level::_ready()
{
    gm = GameManager::get_singleton();

    if (!gm)
    {
        set_process_mode(PROCESS_MODE_DISABLED);
        UtilityFunctions::print(gm);
    }
    else
    {
        set_process_mode(PROCESS_MODE_PAUSABLE);
    }

    //add_child(gm);
}