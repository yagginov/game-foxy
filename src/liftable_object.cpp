#include "liftable_object.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "game_manager.h"
#include "main_character.h"
#include "inventory.h"

using namespace godot;

void LiftableObject::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("_target_spotted", "target_pos"), &LiftableObject::_target_spotted);
	ClassDB::bind_method(D_METHOD("_target_missed"), &LiftableObject::_target_missed);

    ClassDB::bind_method(D_METHOD("get_search_area_path"), &LiftableObject::get_search_area_path);
	ClassDB::bind_method(D_METHOD("set_search_area_path", "p_search_area_path"), &LiftableObject::set_search_area_path);
	ClassDB::add_property("LiftableObject", PropertyInfo(Variant::NODE_PATH, "search_area_path"), "set_search_area_path", "get_search_area_path");

    ClassDB::bind_method(D_METHOD("get_sprite_path"), &LiftableObject::get_sprite_path);
	ClassDB::bind_method(D_METHOD("set_sprite_path", "p_sprite_path"), &LiftableObject::set_sprite_path);
	ClassDB::add_property("LiftableObject", PropertyInfo(Variant::NODE_PATH, "sprite_path"), "set_sprite_path", "get_sprite_path");


    ClassDB::bind_method(D_METHOD("get_item"), &LiftableObject::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "p_item"), &LiftableObject::set_item);
	ClassDB::add_property("LiftableObject", 
        PropertyInfo(
            Variant::OBJECT,
            "item", 
            PROPERTY_HINT_RESOURCE_TYPE,
            Item::get_class_static()), 
        "set_item", 
        "get_item");

}

LiftableObject::LiftableObject() 
{
    is_allowed = false;
}

LiftableObject::~LiftableObject() 
{
    // Add your cleanup here.
    
}

void LiftableObject::_ready() {
    add_to_group("Objects");

    if (has_node(search_area_path))
    {
        search_area = get_node<SearchArea>(search_area_path);
        search_area->connect("target_spotted", Callable(this, "_target_spotted"));
        search_area->connect("target_missed", Callable(this, "_target_missed"));
    }

    if (has_node(sprite_path))
    {
        sprite = get_node<Sprite2D>(sprite_path);
        if (sprite)
        {
            if (item.is_valid())
            {
                sprite->set_texture(item->get_texture());
            }
            else
            {
                sprite->set_texture(nullptr);
            }
        }
    }
}

void LiftableObject::_physics_process(double delta) 
{
    if (is_allowed)
    {
        if (GameManager::get_singleton()->i->is_physical_key_pressed(KEY_E))
        {
            if (GameManager::get_singleton()->mc->get_node<Inventory>("Inventory")->add_item(item))
            {
                queue_free();
            }
        }
    }
}


void LiftableObject::_target_spotted(Vector2 target_pos)
{
    is_allowed = true;
}

void LiftableObject::_target_missed()
{
    is_allowed = false;
}

void LiftableObject::set_search_area_path(const NodePath& p_search_area_path)
{
    search_area_path = p_search_area_path;
}
NodePath LiftableObject::get_search_area_path() const
{
    return search_area_path;
}

void LiftableObject::set_sprite_path(const NodePath& p_sprite_path)
{
    sprite_path = p_sprite_path;
}
NodePath LiftableObject::get_sprite_path() const
{
    return sprite_path;
}

void LiftableObject::set_item(const Ref<Item>& p_item)
{
    item = p_item;
}
Ref<Item> LiftableObject::get_item() const
{
    return item;
}