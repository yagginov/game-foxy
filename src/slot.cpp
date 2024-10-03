#include "slot.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/label_settings.hpp>

#include <godot_cpp/classes/input_event_mouse_button.hpp>


using namespace godot;

void Slot::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("set_item_texture"), &Slot::set_item_texture);
    
    ClassDB::bind_method(D_METHOD("get_item_sprite"), &Slot::get_item_sprite);
	ClassDB::bind_method(D_METHOD("set_item_sprite", "p_item_sprite_path"), &Slot::set_item_sprite);
	ClassDB::add_property("Slot", PropertyInfo(Variant::NODE_PATH, "sprite_item_path"), "set_item_sprite", "get_item_sprite");

    ClassDB::bind_method(D_METHOD("get_item"), &Slot::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "p_item"), &Slot::set_item);
	ClassDB::add_property("Slot", 
        PropertyInfo(
            Variant::OBJECT,
            "item", 
            PROPERTY_HINT_RESOURCE_TYPE,
            Item::get_class_static()), 
        "set_item", 
        "get_item");
    
    ClassDB::bind_method(D_METHOD("get_item_count"), &Slot::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "p_item_count"), &Slot::set_item_count);
	ClassDB::add_property("Slot", PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");

    ClassDB::bind_method(D_METHOD("_mouse_entered"), &Slot::_mouse_entered);
    ClassDB::bind_method(D_METHOD("_mouse_exited"), &Slot::_mouse_exited);

    //ClassDB::bind_method(D_METHOD("_focus_entered"), &Slot::_focus_entered);
    //ClassDB::bind_method(D_METHOD("_focus_exited"), &Slot::_focus_exited);

}

Slot::Slot() 
{
    gm = nullptr;
    item_sprite = nullptr;
    count_label = memnew(Label);
    item_count = 0;
}

Slot::~Slot() 
{
    //memdelete(count_label);
}

void Slot::_ready() 
{
    add_to_group("UI");

    gm = GameManager::get_singleton();

    if (has_node(item_sprite_path)) 
    {
        item_sprite = get_node<Sprite2D>(item_sprite_path);
    }

    if (has_node(NodePath("Sprite2D")))
    {
        background_sprite = get_node<Sprite2D>("Sprite2D");
    }

    connect("mouse_entered", Callable(this, "_mouse_entered"));
    connect("mouse_exited", Callable(this, "_mouse_exited"));

    //connect("focus_entered", Callable(this, "_focus_entered"));
    //connect("focus_exited", Callable(this, "_focus_exited"));

    count_label->set_text("");
    count_label->set_scale(Vector2(0.1, 0.1));
    count_label->set_position(Vector2(14, 14));

    count_label->set_label_settings(ResourceLoader::get_singleton()->load("res://resources/label_settings.tres"));
    this->add_child(count_label);

    update();
}

void Slot::_physics_process(double delta)
{

}

void Slot::_gui_input(Ref<InputEvent> event) 
{
    Ref<InputEventMouseButton> mouse_button_event = event;
    
    if (mouse_button_event.is_valid() && mouse_button_event->is_pressed()) 
    {
        if (mouse_button_event->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) 
        {
            if (gm->is_item_valid())
            {
                gm->end_drag(this);
            }
            else
            {
                if (!is_empty())
                {
                    gm->start_drag(this, item);
                    set_item(nullptr);
                }
            }
            
        }
    }
}

void Slot::_mouse_entered()
{
    background_sprite->set_frame(1);
    gm->set_input_allowed(false);
}
void Slot::_mouse_exited()
{
    background_sprite->set_frame(0);
    gm->set_input_allowed(true);
}

bool Slot::is_empty() const
{
    return item.is_null();
}

void Slot::update()
{
    if (item.is_valid())
    {
        set_item_texture(item->get_texture());
        if (item_count == 0) { item_count = 1; }
        count_label->set_text(String::num(item_count));
    }
    else
    {
        set_item_texture(nullptr);
        item_count = 0;
        count_label->set_text("");
    }
}

bool Slot::add_item(size_t& count)
{
    //UtilityFunctions::print(String::num(item->get_count()) + String(" ") + item->get_name() + String(" added"));
    if (item_count == item->get_max_count())
    {
        return false;
    }

    if (item_count + count <= item->get_max_count())
    {
        item_count += count;
        count = 0;
        return true;
    }

    count -= item->get_max_count() - item_count;
    item_count = item->get_max_count();
    return false;
}

void Slot::set_item_texture(const Ref<Texture2D>& p_texture)
{
    if (item_sprite)
    {
        item_sprite->set_texture(p_texture);
    }
}

void Slot::set_item_sprite(const NodePath& p_item_sprite_path)
{
    item_sprite_path = p_item_sprite_path;
}
NodePath Slot::get_item_sprite() const
{
    return item_sprite_path;
}


void Slot::set_item(const Ref<Item>& p_item)
{
    item = p_item;
    update();
}
Ref<Item> Slot::get_item() const
{
    return item;
}

// Item Count
void Slot::set_item_count(const size_t p_item_count)
{
    if (item.is_null())
    {
        return;
    }

    if (p_item_count >= item->get_max_count())
    {
        item_count = item->get_max_count();
        update();
        return;
    }

    if (p_item_count <= 0)
    {
        set_item(nullptr);
        return;
    }
    item_count = p_item_count;
    update();
}
size_t Slot::get_item_count() const
{
    return item_count;
}