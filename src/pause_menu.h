#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>

#include "game_manager.h"

namespace godot {

class PauseMenu : public Control {
    GDCLASS(PauseMenu, Control)

protected:
    static void _bind_methods();

private:

// temp
    GameManager* gm;
// temp

    Button*             resume;
    Button*             settings;
    Button*             to_main_menu;
    Button*             to_desktop;

    NodePath            resume_path;
    NodePath            settings_path;
    NodePath            to_main_menu_path;
    NodePath            to_desktop_path;

public:
    PauseMenu();
    ~PauseMenu();

    void _ready();
    void _physics_process(double delta) override;

    // listeners
    void            _on_resume_button_pressed();
    void            _on_settings_button_pressed();
    void            _on_to_main_menu_button_pressed();
    void            _on_to_desktop_button_pressed();

    // set / get
    void            set_resume_button(const NodePath& p_resume_button_path);
    NodePath        get_resume_button() const;

    void            set_settings_button(const NodePath& p_settings_button_path);
    NodePath        get_settings_button() const;

    void            set_to_main_menu_button(const NodePath& p_to_main_menu_button_path);
    NodePath        get_to_main_menu_button() const;

    void            set_to_desktop_button(const NodePath& p_to_desktop_button_path);
    NodePath        get_to_desktop_button() const;


};          // class PauseMenu

}           // namespace godot

#endif      // PAUSE_MENU_H
