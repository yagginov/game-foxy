#include "save_button.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

void SaveButton::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_file_path"), &SaveButton::get_file_path);
	ClassDB::bind_method(D_METHOD("set_file_path", "p_file_path"), &SaveButton::set_file_path);
	ClassDB::add_property("SaveButton", PropertyInfo(Variant::STRING, "file_path"), "set_file_path", "get_file_path");

    ClassDB::bind_method(D_METHOD("get_name"), &SaveButton::get_name);
	ClassDB::bind_method(D_METHOD("set_name", "p_name"), &SaveButton::set_name);
	ClassDB::add_property("SaveButton", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");

    ClassDB::bind_method(D_METHOD("get_time"), &SaveButton::get_time);
	ClassDB::bind_method(D_METHOD("set_time", "p_time"), &SaveButton::set_time);
	ClassDB::add_property("SaveButton", PropertyInfo(Variant::STRING, "time"), "set_time", "get_time");

    ClassDB::bind_method(D_METHOD("get_function"), &SaveButton::get_function);
	ClassDB::bind_method(D_METHOD("set_function", "p_function"), &SaveButton::set_function);
	ClassDB::add_property("SaveButton", PropertyInfo(Variant::STRING, "function"), "set_function", "get_function");
}

SaveButton::SaveButton() 
{
    file_path = "";
    name = "";
    time = "";
    description = "";
    function = "";
}

SaveButton::~SaveButton() 
{

}

void SaveButton::_ready() 
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


}

void SaveButton::_pressed()
{
    if (gm->has_method(function))
    {
        gm->call(function, file_path);
    }
}


void SaveButton::set_file_path(const String& p_file_path)
{
    file_path = p_file_path;
}
String SaveButton::get_file_path() const
{
    return file_path;
}

void SaveButton::set_name(const String& p_name)
{
    name = p_name;
    if(has_node("MarginContainer/VBoxContainer/Name"))
    {
        Label* label = get_node<Label>("MarginContainer/VBoxContainer/Name");
        label->set_text(name);
    }
}
String SaveButton::get_name() const
{
    return name;
}

void SaveButton::set_time(const String& p_time)
{
    time = p_time;
    if(has_node("MarginContainer/VBoxContainer/Time"))
    {
        Label* label = get_node<Label>("MarginContainer/VBoxContainer/Time");
        label->set_text(time);
    }
}
String SaveButton::get_time() const
{
    return time;
}

void SaveButton::set_description(const String& p_description)
{
    description = p_description;
    if(has_node("MarginContainer/VBoxContainer/Description"))
    {
        Label* label = get_node<Label>("MarginContainer/VBoxContainer/Description");
        label->set_text(description);
    }
}
String SaveButton::get_description() const
{
    return description;
}

void SaveButton::set_function(const String& p_function)
{
    function = p_function;
}
String SaveButton::get_function() const
{
    return function;
}