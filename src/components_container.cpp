#include "components_container.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ComponentsContainer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_health_path"), &ComponentsContainer::get_health_path);
	ClassDB::bind_method(D_METHOD("set_health_path", "p_health_path"), &ComponentsContainer::set_health_path);
	ClassDB::add_property("ComponentsContainer", PropertyInfo(Variant::NODE_PATH, "health_path"), "set_health_path", "get_health_path");

    ClassDB::bind_method(D_METHOD("get_hitbox_path"), &ComponentsContainer::get_hitbox_path);
	ClassDB::bind_method(D_METHOD("set_hitbox_path", "p_hitbox_path"), &ComponentsContainer::set_hitbox_path);
	ClassDB::add_property("ComponentsContainer", PropertyInfo(Variant::NODE_PATH, "hitbox_path"), "set_hitbox_path", "get_hitbox_path");

    ClassDB::bind_method(D_METHOD("get_hurtbox_path"), &ComponentsContainer::get_hurtbox_path);
	ClassDB::bind_method(D_METHOD("set_hurtbox_path", "p_hurtbox_path"), &ComponentsContainer::set_hurtbox_path);
	ClassDB::add_property("ComponentsContainer", PropertyInfo(Variant::NODE_PATH, "hurtbox_path"), "set_hurtbox_path", "get_hurtbox_path");

    ClassDB::bind_method(D_METHOD("get_animation_controller_path"), &ComponentsContainer::get_animation_controller_path);
	ClassDB::bind_method(D_METHOD("set_animation_controller_path", "p_animation_controller_path"), &ComponentsContainer::set_animation_controller_path);
	ClassDB::add_property("ComponentsContainer", PropertyInfo(Variant::NODE_PATH, "animation_controller_path"), "set_animation_controller_path", "get_animation_controller_path");

    ClassDB::bind_method(D_METHOD("get_search_area_path"), &ComponentsContainer::get_search_area_path);
	ClassDB::bind_method(D_METHOD("set_search_area_path", "p_search_area_path"), &ComponentsContainer::set_search_area_path);
	ClassDB::add_property("ComponentsContainer", PropertyInfo(Variant::NODE_PATH, "search_area_path"), "set_search_area_path", "get_search_area_path");
}

ComponentsContainer::ComponentsContainer()
{
    health = nullptr;
    hitbox = nullptr;
    hurtbox = nullptr;
    animation_controller = nullptr;
    search_area = nullptr;
}

ComponentsContainer::~ComponentsContainer()
{

}

void ComponentsContainer::_ready()
{
    if (has_node(health_path)) {
        health = get_node<HealthComponent>(health_path); 
    }

    if (has_node(hitbox_path)) {
        hitbox = get_node<Hitbox>(hitbox_path); 
    }

    if (has_node(hurtbox_path)) {
        hurtbox = get_node<Hurtbox>(hurtbox_path); 
    }

    if (has_node(animation_controller_path)) {
        animation_controller = get_node<AnimationController>(animation_controller_path); 
    }

    if (has_node(search_area_path)) {
        search_area = get_node<SearchArea>(search_area_path); 
    }
}


void ComponentsContainer::bind(Actor* mother_pointer)
{
    if (health)
    {
        health->connect("dead", Callable(mother_pointer, "_dead"));
    }

    if (hitbox)
    {
        hitbox->connect("hit", Callable(mother_pointer, "_hit"));
    }

    if (hurtbox)
    {
        hurtbox->connect("damage", Callable(mother_pointer, "_damage"));
    }

    if (search_area)
    {
        search_area->connect("target_spotted", Callable(mother_pointer, "_target_spotted"));
        search_area->connect("target_missed", Callable(mother_pointer, "_target_missed"));
    }
}



void ComponentsContainer::set_health_path(const NodePath& p_health_path)
{
    health_path = p_health_path;
}
NodePath ComponentsContainer::get_health_path() const
{
    return health_path;
}

void ComponentsContainer::set_hitbox_path(const NodePath& p_hitbox_path)
{
    hitbox_path = p_hitbox_path;
}
NodePath ComponentsContainer::get_hitbox_path() const
{
    return hitbox_path;
}

void ComponentsContainer::set_hurtbox_path(const NodePath& p_hurtbox_path)
{
    hurtbox_path = p_hurtbox_path;
}
NodePath ComponentsContainer::get_hurtbox_path() const
{
    return hurtbox_path;
}

void ComponentsContainer::set_animation_controller_path(const NodePath& p_animation_controller_path)
{
    animation_controller_path = p_animation_controller_path;
}
NodePath ComponentsContainer::get_animation_controller_path() const
{
    return animation_controller_path;
}

void ComponentsContainer::set_search_area_path(const NodePath& p_search_area_path)
{
    search_area_path = p_search_area_path;
}
NodePath ComponentsContainer::get_search_area_path() const
{
    return search_area_path;
}