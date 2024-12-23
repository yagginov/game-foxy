#include "dialog_window.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

void DialogWindow::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("_on_cancel_button_pressed"), &DialogWindow::_on_cancel_button_pressed);
	ClassDB::bind_method(D_METHOD("_on_ok_button_pressed"), &DialogWindow::_on_ok_button_pressed);

    ClassDB::bind_method(D_METHOD("get_cancel_button"), &DialogWindow::get_cancel_button);
	ClassDB::bind_method(D_METHOD("set_cancel_button", "p_cancel_button_path"), &DialogWindow::set_cancel_button);
	ClassDB::add_property("DialogWindow", PropertyInfo(Variant::NODE_PATH, "cancel_path"), "set_cancel_button", "get_cancel_button");

    ClassDB::bind_method(D_METHOD("get_ok_button"), &DialogWindow::get_ok_button);
	ClassDB::bind_method(D_METHOD("set_ok_button", "p_ok_button_path"), &DialogWindow::set_ok_button);
	ClassDB::add_property("DialogWindow", PropertyInfo(Variant::NODE_PATH, "ok_path"), "set_ok_button", "get_ok_button");

    ClassDB::bind_method(D_METHOD("get_label"), &DialogWindow::get_label);
	ClassDB::bind_method(D_METHOD("set_label", "p_label_path"), &DialogWindow::set_label);
	ClassDB::add_property("DialogWindow", PropertyInfo(Variant::NODE_PATH, "label_path"), "set_label", "get_label");

    ClassDB::bind_method(D_METHOD("get_text_edit"), &DialogWindow::get_text_edit);
	ClassDB::bind_method(D_METHOD("set_text_edit", "p_text_edit_path"), &DialogWindow::set_text_edit);
	ClassDB::add_property("DialogWindow", PropertyInfo(Variant::NODE_PATH, "text_edit_path"), "set_text_edit", "get_text_edit");
}

DialogWindow::DialogWindow() 
{
    answer = Answer::NO_REQUEST;
    cancel = nullptr;
    ok = nullptr;
    label = nullptr;
    text_edit = nullptr;
}

DialogWindow::~DialogWindow() 
{

}

void DialogWindow::_ready() 
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

    if (has_node(cancel_path)) 
    {
        cancel = get_node<Button>(cancel_path);
    }
    if (cancel)
    {
        cancel->connect("pressed", Callable(this, "_on_cancel_button_pressed"));
    }

    if (has_node(ok_path)) 
    {
        ok = get_node<Button>(ok_path);
    }
    if (ok)
    {
        ok->connect("pressed", Callable(this, "_on_ok_button_pressed"));
    }

    if (has_node(label_path)) 
    {
        label = get_node<Label>(label_path);
    }

    if (has_node(text_edit_path)) 
    {
        text_edit = get_node<TextEdit>(text_edit_path);
    }
}

void DialogWindow::call(String p_label_text)
{
    answer = Answer::CANCEL;

    if (label)
    {
        label->set_text(p_label_text);
    }

    if (text_edit)
    {
        text_edit->set_text("");
        text_edit->set_placeholder("savefile");
    }

    this->show();
}

String DialogWindow::get_text_answer() const
{
    return text_answer;
}

bool DialogWindow::answer_is_ok() const
{
    return answer == Answer::OK;
}

void DialogWindow::_on_cancel_button_pressed()
{
    if (!cancel)
    {
        return;
    }

    answer = Answer::CANCEL;

    this->hide();
}
void DialogWindow::_on_ok_button_pressed()
{
    if (!ok)
    {
        return;
    }

    answer = Answer::OK;
    

    this->hide();
}


void DialogWindow::set_cancel_button(const NodePath& p_cancel_button_path)
{
    cancel_path = p_cancel_button_path;
}
NodePath DialogWindow::get_cancel_button() const
{
    return cancel_path;
}

void DialogWindow::set_ok_button(const NodePath& p_ok_button_path)
{
    ok_path = p_ok_button_path;
}
NodePath DialogWindow::get_ok_button() const
{
    return ok_path;
}

void DialogWindow::set_label(const NodePath& p_label_path)
{
    label_path = p_label_path;
}
NodePath DialogWindow::get_label() const
{
    return label_path;
}

void DialogWindow::set_text_edit(const NodePath& p_text_edit_path)
{
    text_edit_path = p_text_edit_path;
}
NodePath DialogWindow::get_text_edit() const
{
    return text_edit_path;
}