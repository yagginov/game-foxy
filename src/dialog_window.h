#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>

#include <godot_cpp/classes/text_edit.hpp>
#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/templates/vector.hpp>

#include "game_manager.h"
#include "save_button.h"

namespace godot {

class DialogWindow : public Control {
    GDCLASS(DialogWindow, Control)

protected:
    static void         _bind_methods();

public:
    enum                Answer
    {
        OK = 0,
        CANCEL = 1,
        NO_REQUEST = 2
    };

private:
    GameManager*        gm;

    Answer              answer;
    String              text_answer;
    Node2D*             requester;
    String              function;

    Button*             cancel;
    Button*             ok;
    Label*              label;
    TextEdit*           text_edit;

    NodePath            cancel_path;
    NodePath            ok_path;
    NodePath            label_path;
    NodePath            text_edit_path;


public:
    DialogWindow();
    ~DialogWindow();

    void _ready();

    // void call(Node2D* p_requester, String p_function);
    void call(String p_label_text);

    String get_text_answer() const;
    bool answer_is_ok() const;

    // listeners
    void            _on_cancel_button_pressed();
    void            _on_ok_button_pressed();

    // set / get
    void            set_cancel_button(const NodePath& p_cancel_button_path);
    NodePath        get_cancel_button() const;
    void            set_ok_button(const NodePath& p_ok_button_path);
    NodePath        get_ok_button() const;
    void            set_label(const NodePath& p_label_path);
    NodePath        get_label() const;
    void            set_text_edit(const NodePath& p_text_edit_path);
    NodePath        get_text_edit() const;

};          // class DialogWindow

}           // namespace godot

#endif      // DIALOG_WINDOW_H
