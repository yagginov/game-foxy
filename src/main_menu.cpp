#include "main_menu.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void MainMenu::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_play_button_pressed"), &MainMenu::_on_play_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_settings_button_pressed"), &MainMenu::_on_settings_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_quit_button_pressed"), &MainMenu::_on_quit_button_pressed);

    ClassDB::bind_method(D_METHOD("get_play_button"), &MainMenu::get_play_button);
	ClassDB::bind_method(D_METHOD("set_play_button", "p_play_button_path"), &MainMenu::set_play_button);
	ClassDB::add_property("MainMenu", PropertyInfo(Variant::NODE_PATH, "play_path"), "set_play_button", "get_play_button");

    ClassDB::bind_method(D_METHOD("get_settings_button"), &MainMenu::get_settings_button);
	ClassDB::bind_method(D_METHOD("set_settings_button", "p_settings_button_path"), &MainMenu::set_settings_button);
	ClassDB::add_property("MainMenu", PropertyInfo(Variant::NODE_PATH, "settings_path"), "set_settings_button", "get_settings_button");

    ClassDB::bind_method(D_METHOD("get_quit_button"), &MainMenu::get_quit_button);
	ClassDB::bind_method(D_METHOD("set_quit_button", "p_quit_button_path"), &MainMenu::set_quit_button);
	ClassDB::add_property("MainMenu", PropertyInfo(Variant::NODE_PATH, "quit_path"), "set_quit_button", "get_quit_button");
}

MainMenu::MainMenu() 
{
    play = nullptr;
    settings = nullptr;
    quit = nullptr;
}

MainMenu::~MainMenu() 
{

}

void MainMenu::_ready() 
{
    add_to_group("UI");

    if (has_node(play_path)) 
    {
        play = get_node<Button>(play_path);
    }
    if (play)
    {
        play->connect("pressed", Callable(this, "_on_play_button_pressed"));
    }

    if (has_node(settings_path)) 
    {
        settings = get_node<Button>(settings_path);
    }
    if (settings)
    {
        settings->connect("pressed", Callable(this, "_on_settings_button_pressed"));
    }

    if (has_node(quit_path)) 
    {
        quit = get_node<Button>(quit_path);
    }
    if (quit)
    {
        quit->connect("pressed", Callable(this, "_on_quit_button_pressed"));
    }
    
}

void MainMenu::_physics_process(double delta)
{

}

void MainMenu::_on_play_button_pressed()
{
    if (!play)
    {
        return;
    }
    this->get_tree()->change_scene_to_file("res://scenes/test_level.tscn");
}

void MainMenu::_on_settings_button_pressed()
{
    if (!settings)
    {
        return;
    }
}

void MainMenu::_on_quit_button_pressed()
{
    if (!quit)
    {
        return;
    }
    this->get_tree()->quit();
}


void MainMenu::set_play_button(const NodePath& p_play_button_path)
{
    play_path = p_play_button_path;
}
NodePath MainMenu::get_play_button() const
{
    return play_path;
}

void MainMenu::set_settings_button(const NodePath& p_settings_button_path)
{
    settings_path = p_settings_button_path;
}
NodePath MainMenu::get_settings_button() const
{
    return settings_path;
}

void MainMenu::set_quit_button(const NodePath& p_quit_button_path)
{
    quit_path = p_quit_button_path;
}
NodePath MainMenu::get_quit_button() const
{
    return quit_path;
}