#include "level.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "main_character.h"

#include <iostream>

using namespace godot;

void Level::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_name"), &Level::get_name);
	ClassDB::bind_method(D_METHOD("set_name", "p_name"), &Level::set_name);
	ClassDB::add_property("Level", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");

    ClassDB::bind_method(D_METHOD("get_scene_path"), &Level::get_scene_path);
	ClassDB::bind_method(D_METHOD("set_scene_path", "p_scene_path"), &Level::set_scene_path);
	ClassDB::add_property("Level", PropertyInfo(Variant::STRING, "scene_path"), "set_scene_path", "get_scene_path");

    ClassDB::bind_method(D_METHOD("save"), &Level::save);
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
        gm->give_current_level(this);
    }
}

void Level::set_name(const String& p_name)
{
    name = p_name;
}
String Level::get_name() const
{
    return name;
}

void Level::set_scene_path(const String& p_scene_path)
{
    scene_path = p_scene_path;
}
String Level::get_scene_path() const
{
    return scene_path;
}

Dictionary Level::save()
{
    Dictionary level_data;
    level_data["scene_path"] = scene_path;

    Array children = get_children();
    
    for (int i = 0; i < children.size(); i++) {
        Node *child_node = Object::cast_to<Node>(children[i]);

        if (child_node) 
        {
            if (!child_node->is_in_group("Player")) 
            {
                if (child_node->has_method("save")) 
                {
                    Dictionary child_save_data = child_node->call("save");
                    String node_name = child_node->get_name();
                    //UtilityFunctions::print(node_name);
                    level_data[node_name] = child_save_data;
                }
            }
        }
    }

    return level_data;
}