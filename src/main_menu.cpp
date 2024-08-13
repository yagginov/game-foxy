#include "main_menu.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void MainMenu::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_play_button_pressed"), &MainMenu::_on_play_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_settings_button_pressed"), &MainMenu::_on_settings_button_pressed);
    ClassDB::bind_method(D_METHOD("_on_quit_button_pressed"), &MainMenu::_on_quit_button_pressed);
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