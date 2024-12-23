#include "load_menu.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

void LoadMenu::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_back_button_pressed"), &LoadMenu::_on_back_button_pressed);

    ClassDB::bind_method(D_METHOD("get_back_button"), &LoadMenu::get_back_button);
	ClassDB::bind_method(D_METHOD("set_back_button", "p_back_button_path"), &LoadMenu::set_back_button);
	ClassDB::add_property("LoadMenu", PropertyInfo(Variant::NODE_PATH, "back_path"), "set_back_button", "get_back_button");

}

LoadMenu::LoadMenu() 
{
    back = nullptr;

}

LoadMenu::~LoadMenu() 
{

}

void LoadMenu::_ready() 
{
    add_to_group("UI");

    gm = GameManager::get_singleton();
    if (!gm)
    {
        set_process_mode(PROCESS_MODE_DISABLED);
    }
    else
    {
        set_process_mode(PROCESS_MODE_ALWAYS);
    }

    if (has_node(back_path)) 
    {
        back = get_node<Button>(back_path);
    }
    if (back)
    {
        back->connect("pressed", Callable(this, "_on_back_button_pressed"));
    }
}

void LoadMenu::_on_back_button_pressed()
{
    if (!back)
    {
        return;
    }
    this->hide();
}


void LoadMenu::set_back_button(const NodePath& p_back_button_path)
{
    back_path = p_back_button_path;
}
NodePath LoadMenu::get_back_button() const
{
    return back_path;
}

SaveButton* LoadMenu::add_new_button(String p_name, String p_function, String p_file_path)
{
    VBoxContainer *container = nullptr;
    if (has_node("NinePatchRect/VBoxContainer/MarginContainer2/ScrollContainer/VBoxContainer"))
    {
        container = get_node<VBoxContainer>("NinePatchRect/VBoxContainer/MarginContainer2/ScrollContainer/VBoxContainer");
    }
    else
    {
        ERR_PRINT("Failed to load VBoxContainer");
        return nullptr;
    }
    

    Ref<PackedScene> save_button_scene = ResourceLoader::get_singleton()->load("res://scenes/save_button.tscn");

    if (save_button_scene.is_null()) {
        ERR_PRINT("Failed to load scene save_button.tscn");
        return nullptr;
    }

    SaveButton *save_button_instance = Object::cast_to<SaveButton>(save_button_scene->instantiate());

    if (!save_button_instance) {
        ERR_PRINT("Failed to create SaveButton instance");
        return nullptr;
    }

    save_button_instance->set_name(p_name);
    save_button_instance->set_function(p_function);
    save_button_instance->set_file_path(p_file_path);

    container->add_child(save_button_instance);

    return save_button_instance;
}


void LoadMenu::initialize_load()
{
    Ref<DirAccess> dir = DirAccess::open("res://saves");

    if (dir.is_null()) {
        ERR_PRINT("Could not open directory res://saves");
        return;
    }

    if (dir->list_dir_begin() == OK) {
        String file_name;
        while (!(file_name = dir->get_next()).is_empty()) {
            if (dir->current_is_dir() || file_name.begins_with(".")) {
                continue;
            }

            if (file_name.get_extension() == "json") {
                if (file_names.count(file_name))
                {
                    continue;
                }
                else
                {
                    file_names.push_back(file_name);
                }

                String name = file_name.get_basename();
                SaveButton *save_button_instance = add_new_button(name, "load", "res://saves/" + file_name);
            }
        }

        dir->list_dir_end();
    }
}

void LoadMenu::initialize_save()
{
    Ref<DirAccess> dir = DirAccess::open("res://saves");

    if (dir.is_null()) {
        ERR_PRINT("Could not open directory res://saves");
        return;
    }

    if (!new_save_button || new_save_button->get_function() != "new_save")
    {
        new_save_button = add_new_button("New Save", "new_save", ""); 
    }

    if (dir->list_dir_begin() == OK) {
        String file_name;
        while (!(file_name = dir->get_next()).is_empty()) {
            if (dir->current_is_dir() || file_name.begins_with(".")) {
                continue;
            }

            if (file_name.get_extension() == "json") {
                if (file_names.count(file_name))
                {
                    continue;
                }
                else
                {
                    file_names.push_back(file_name);
                }

                String name = file_name.get_basename();
                SaveButton *save_button_instance = add_new_button(name, "save", "res://saves/" + file_name);
            }
        }

        dir->list_dir_end();
    }
}