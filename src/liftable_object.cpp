#include "liftable_object.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/label_settings.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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

    ClassDB::bind_method(D_METHOD("get_velocity_component"), &LiftableObject::get_velocity_component);
	ClassDB::bind_method(D_METHOD("set_velocity_component", "p_velocity_component"), &LiftableObject::set_velocity_component);
	ClassDB::add_property("LiftableObject", 
        PropertyInfo(
            Variant::OBJECT,
            "velocity_component", 
            PROPERTY_HINT_RESOURCE_TYPE,
            VelocityComponent::get_class_static()), 
        "set_velocity_component", 
        "get_velocity_component");

}

LiftableObject::LiftableObject():
LiftableObject(nullptr)
{
}

LiftableObject::LiftableObject(const Ref<Item>& p_item):
item(p_item) 
{
    is_allowed = false;
    sprite = nullptr;
    search_area = nullptr;
    gm = nullptr;
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
        set_item(item);
    }

    gm = GameManager::get_singleton();

}

void LiftableObject::_physics_process(double delta) 
{
    if (is_allowed)
    {
        if (gm->i->is_physical_key_pressed(KEY_E))
        {
            if (gm->mc->get_node<Inventory>("Inventory")->add_item(item))
            {
                queue_free();
            }
        }
    }

    if (velocity_component.is_valid())
    {
        set_global_position(get_global_position() + velocity_component->move(delta));
        if (!velocity_component->get_current_speed())
        {
            velocity_component.unref();
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
    if (item.is_valid() && sprite)
    {
        sprite->set_texture(item->get_texture());
    }
}
Ref<Item> LiftableObject::get_item() const
{
    return item;
}

void LiftableObject::set_velocity_component(const Ref<VelocityComponent>& p_velocity_component)
{
    velocity_component = p_velocity_component;
}
Ref<VelocityComponent> LiftableObject::get_velocity_component() const
{
    return velocity_component;
}