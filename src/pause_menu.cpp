#include "pause_menu.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void PauseMenu::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_resume_button_pressed"), &PauseMenu::_on_resume_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_settings_button_pressed"), &PauseMenu::_on_settings_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_to_main_menu_button_pressed"), &PauseMenu::_on_to_main_menu_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_to_desktop_button_pressed"), &PauseMenu::_on_to_desktop_button_pressed);

    ClassDB::bind_method(D_METHOD("get_resume_button"), &PauseMenu::get_resume_button);
	ClassDB::bind_method(D_METHOD("set_resume_button", "p_resume_button_path"), &PauseMenu::set_resume_button);
	ClassDB::add_property("PauseMenu", PropertyInfo(Variant::NODE_PATH, "resume_path"), "set_resume_button", "get_resume_button");

    ClassDB::bind_method(D_METHOD("get_settings_button"), &PauseMenu::get_settings_button);
	ClassDB::bind_method(D_METHOD("set_settings_button", "p_settings_button_path"), &PauseMenu::set_settings_button);
	ClassDB::add_property("PauseMenu", PropertyInfo(Variant::NODE_PATH, "settings_path"), "set_settings_button", "get_settings_button");

    ClassDB::bind_method(D_METHOD("get_to_main_menu_button"), &PauseMenu::get_to_main_menu_button);
	ClassDB::bind_method(D_METHOD("set_to_main_menu_button", "p_to_main_menu_button_path"), &PauseMenu::set_to_main_menu_button);
	ClassDB::add_property("PauseMenu", PropertyInfo(Variant::NODE_PATH, "to_main_menu_path"), "set_to_main_menu_button", "get_to_main_menu_button");

    ClassDB::bind_method(D_METHOD("get_to_desktop_button"), &PauseMenu::get_to_desktop_button);
	ClassDB::bind_method(D_METHOD("set_to_desktop_button", "p_to_desktop_button_path"), &PauseMenu::set_to_desktop_button);
	ClassDB::add_property("PauseMenu", PropertyInfo(Variant::NODE_PATH, "to_desktop_path"), "set_to_desktop_button", "get_to_desktop_button");
}

PauseMenu::PauseMenu() 
{
    resume = nullptr;
    settings = nullptr;
    to_main_menu = nullptr;
    to_desktop = nullptr;

// temp
    i = Input::get_singleton();
// temp
}

PauseMenu::~PauseMenu() 
{

}

void PauseMenu::_ready() 
{
    add_to_group("UI");

    if (has_node(resume_path)) 
    {
        resume = get_node<Button>(resume_path);
    }
    if (resume)
    {
        resume->connect("pressed", Callable(this, "_on_resume_button_pressed"));
    }

    if (has_node(settings_path)) 
    {
        settings = get_node<Button>(settings_path);
    }
    if (settings)
    {
        settings->connect("pressed", Callable(this, "_on_settings_button_pressed"));
    }

    if (has_node(to_main_menu_path)) 
    {
        to_main_menu = get_node<Button>(to_main_menu_path);
    }
    if (to_main_menu)
    {
        to_main_menu->connect("pressed", Callable(this, "_on_to_main_menu_button_pressed"));
    }

    if (has_node(to_desktop_path)) 
    {
        to_desktop = get_node<Button>(to_desktop_path);
    }
    if (to_desktop)
    {
        to_desktop->connect("pressed", Callable(this, "_on_to_desktop_button_pressed"));
    }
    
}

void PauseMenu::_physics_process(double delta)
{
    if (i->is_action_just_pressed("ui_cancel"))
    {
        if (this->get_tree()->is_paused())
        {
            this->hide();
            this->get_tree()->set_pause(false);
        }
        else
        {
            this->show();
            this->get_tree()->set_pause(true);
        }
    }
}

void PauseMenu::_on_resume_button_pressed()
{
    if (!resume)
    {
        return;
    }

    this->hide();
    this->get_tree()->set_pause(false);
}

void PauseMenu::_on_settings_button_pressed()
{
    if (!settings)
    {
        return;
    }
}

void PauseMenu::_on_to_main_menu_button_pressed()
{
    if (!to_main_menu)
    {
        return;
    }
    this->hide();
    this->get_tree()->set_pause(false);
    this->get_tree()->change_scene_to_file("res://scenes/main_menu.tscn");
}

void PauseMenu::_on_to_desktop_button_pressed()
{
    if (!to_desktop)
    {
        return;
    }
    this->hide();
    this->get_tree()->set_pause(false);
    this->get_tree()->quit();
}


void PauseMenu::set_resume_button(const NodePath& p_resume_button_path)
{
    resume_path = p_resume_button_path;
}
NodePath PauseMenu::get_resume_button() const
{
    return resume_path;
}

void PauseMenu::set_settings_button(const NodePath& p_settings_button_path)
{
    settings_path = p_settings_button_path;
}
NodePath PauseMenu::get_settings_button() const
{
    return settings_path;
}

void PauseMenu::set_to_main_menu_button(const NodePath& p_to_main_menu_button_path)
{
    to_main_menu_path = p_to_main_menu_button_path;
}
NodePath PauseMenu::get_to_main_menu_button() const
{
    return to_main_menu_path;
}

void PauseMenu::set_to_desktop_button(const NodePath& p_to_desktop_button_path)
{
    to_desktop_path = p_to_desktop_button_path;
}
NodePath PauseMenu::get_to_desktop_button() const
{
    return to_desktop_path;
}