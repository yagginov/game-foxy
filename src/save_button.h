#ifndef SAVE_BUTTON_H
#define SAVE_BUTTON_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/variant/string.hpp>

#include "game_manager.h"

namespace godot {

class SaveButton : public Button {
    GDCLASS(SaveButton, Button)

protected:
    static void         _bind_methods();

private:
    GameManager*        gm;
    String              file_path;
    String              name;
    String              time;
    String              description;

    String              function;

public:
    SaveButton();
    ~SaveButton();

    void _ready();

    void _pressed() override;

    // set / get
    void                set_file_path(const String& p_file_path);
    String              get_file_path() const;

    void                set_name(const String& p_name);
    String              get_name() const;

    void                set_time(const String& p_time);
    String              get_time() const;

    void                set_description(const String& p_description);
    String              get_description() const;

    void                set_function(const String& p_function);
    String              get_function() const;

};          // class SaveButton

}           // namespace godot

#endif      // SAVE_BUTTON_H
