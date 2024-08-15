#include "game_manager.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


void GameManager::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_main_character_path"), &GameManager::get_main_character_path);
	ClassDB::bind_method(D_METHOD("set_main_character_path", "p_main_character_path"), &GameManager::set_main_character_path);
	ClassDB::add_property("GameManager", PropertyInfo(Variant::NODE_PATH, "main_character_path"), "set_main_character_path", "get_main_character_path");
}

MainCharacter* GameManager::get_main_character() const
{
    return MC;
}

NodePath GameManager::get_main_character_path() const
{
    return main_character_path;
}
void GameManager::set_main_character_path(const MainCharacter* p_main_character_path)
{
    main_character_path = p_MC;
}