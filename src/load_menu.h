#ifndef LOAD_MENU_H
#define LOAD_MENU_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>

#include "game_manager.h"
#include "save_button.h"

namespace godot {

class LoadMenu : public Control {
    GDCLASS(LoadMenu, Control)

protected:
    static void         _bind_methods();

private:
    GameManager*        gm;

    Button*             back;

    NodePath            back_path;

public:
    LoadMenu();
    ~LoadMenu();

    void _ready();

    // listeners
    void            _on_back_button_pressed();

    // set / get
    void            set_back_button(const NodePath& p_back_button_path);
    NodePath        get_back_button() const;

    SaveButton* add_new_button();

    void initialize_load();
    void initialize_save();


};          // class LoadMenu

}           // namespace godot

#endif      // LOAD_MENU_H
