#include "item.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Item::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_name"), &Item::get_name);
	ClassDB::bind_method(D_METHOD("set_name", "p_name"), &Item::set_name);
	ClassDB::add_property("Item", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");

    ClassDB::bind_method(D_METHOD("get_texture"), &Item::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "p_texture"), &Item::set_texture);
	ClassDB::add_property("Item", PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");

    ClassDB::bind_method(D_METHOD("get_max_count"), &Item::get_max_count);
	ClassDB::bind_method(D_METHOD("set_max_count", "p_max_count"), &Item::set_max_count);
	ClassDB::add_property("Item", PropertyInfo(Variant::INT, "max_count"), "set_max_count", "get_max_count");

    ClassDB::bind_method(D_METHOD("get_resource_path"), &Item::get_resource_path);
	ClassDB::bind_method(D_METHOD("set_resource_path", "p_resource_path"), &Item::set_resource_path);
	ClassDB::add_property("Item", PropertyInfo(Variant::STRING, "resource_path"), "set_resource_path", "get_resource_path");
}

Item::Item() 
{
    gm = nullptr;
    name = "";
    max_count = 4;
    resource_path = "";
}

Item::Item(const Item& other) 
{
    this->name = other.name;
    this->max_count = other.max_count;
    this->texture = other.texture;
    this->resource_path = other.resource_path;
    this->gm = other.gm;
}

Item::~Item() 
{
    // Add your cleanup here.
}

bool Item::use_item()
{
    if (!gm)
    {
        gm = GameManager::get_singleton();
    }
    return true;
}

// Name
void Item::set_name(const String p_name)
{
    name = p_name;
}
String Item::get_name() const
{
    return name;
}

// Texture
void Item::set_texture(const Ref<Texture2D>& p_texture)
{
    texture = p_texture;
}
Ref<Texture2D> Item::get_texture() const
{
    return texture;
}

// Max Count
void Item::set_max_count(const size_t p_max_count)
{
    max_count = p_max_count;
}
size_t Item::get_max_count() const
{
    return max_count;
}

// Name
void Item::set_resource_path(const String p_resource_path)
{
    resource_path = p_resource_path;
}
String Item::get_resource_path() const
{
    return resource_path;
}