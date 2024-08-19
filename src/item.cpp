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
}

Item::Item() 
{
    gm = GameManager::get_singleton();

    name = "";
    texture = nullptr;
}

Item::~Item() 
{
    // Add your cleanup here.
}

void Item::use_item()
{
    
}

void Item::set_name(const String p_name)
{
    name = p_name;
}
String Item::get_name() const
{
    return name;
}

void Item::set_texture(Texture2D* p_texture)
{
    texture = p_texture;
}
Texture2D* Item::get_texture() const
{
    return texture;
}
