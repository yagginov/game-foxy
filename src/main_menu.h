#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/button.hpp"

namespace godot {

class MainMenu : public Control {
    GDCLASS(MainMenu, Control)

protected:
    static void _bind_methods();

private:

    Button*             play;
    Button*             load;
    Button*             settings;
    Button*             quit;

    NodePath            play_path;
    NodePath            load_path;
    NodePath            settings_path;
    NodePath            quit_path;

public:
    MainMenu();
    ~MainMenu();

    void _ready();
    void _physics_process(double delta) override;

    // listeners
    void            _on_play_button_pressed();
    void            _on_load_button_pressed();
    void            _on_settings_button_pressed();
    void            _on_quit_button_pressed();

    // set / get
    void            set_play_button(const NodePath& p_play_button_path);
    NodePath        get_play_button() const;

    void            set_load_button(const NodePath& p_load_button_path);
    NodePath        get_load_button() const;

    void            set_settings_button(const NodePath& p_settings_button_path);
    NodePath        get_settings_button() const;

    void            set_quit_button(const NodePath& p_quit_button_path);
    NodePath        get_quit_button() const;

};          // class MainMenu

}           // namespace godot

#endif      // MAIN_MENU_H
