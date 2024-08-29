#include "slot.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


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

}

Slot::Slot() 
{
    item_sprite = nullptr;
}

Slot::~Slot() 
{

}

void Slot::_ready() 
{
    add_to_group("UI");

    if (has_node(item_sprite_path)) 
    {
        item_sprite = get_node<Sprite2D>(item_sprite_path);
    }
    
}

void Slot::_physics_process(double delta)
{

}

bool Slot::is_empty() const
{
    return item.is_null();
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
    if (item.is_valid())
    {
        set_item_texture(item->get_texture());
    }
    else
    {
        set_item_texture(nullptr);
    }
}
Ref<Item> Slot::get_item() const
{
    return item;
}