#include "inventory.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

void Inventory::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("set_items", "items"), &Inventory::set_items);
    ClassDB::bind_method(D_METHOD("get_items"), &Inventory::get_items);
    ADD_PROPERTY(
        PropertyInfo(
            Variant::ARRAY, 
            "items", 
            PROPERTY_HINT_ARRAY_TYPE, 
            String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + String(":") + Item::get_class_static()), 
        "set_items", 
        "get_items");

    ClassDB::bind_method(D_METHOD("set_slots", "slots"), &Inventory::set_slots);
    ClassDB::bind_method(D_METHOD("get_slots"), &Inventory::get_slots);
    ADD_PROPERTY(PropertyInfo(
            Variant::ARRAY, 
            "slots", 
            PROPERTY_HINT_NODE_TYPE, 
            String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_NODE_TYPE) + String(":") + Slot::get_class_static()), 
        "set_slots", 
        "get_slots");    

    ClassDB::bind_method(D_METHOD("update"), &Inventory::update);

}

Inventory::Inventory() 
{
    items = TypedArray<Item>();
    slots = TypedArray<Slot>();
    gm = nullptr;
}

Inventory::~Inventory() 
{
    // Add your cleanup here.
}

void Inventory::_ready() 
{
    add_to_group("UI");

    gm = GameManager::get_singleton();
}

void Inventory::_physics_process(double delta) 
{
    
}

void Inventory::update()
{
    for (int i = 0; i < items.size(); ++i)
    {
        Item* item = Object::cast_to<Item>(items[i]);
        Slot* slot = Object::cast_to<Slot>(slots[i]);
        
        if (item)
        {
            slot->set_item_texture(item->get_texture());
        }
        else
        {
            slot->set_item_texture(nullptr);
        }
    }
}



void Inventory::set_items(const TypedArray<Item>& new_items)
{ 
    items = new_items; 
    update();
}
TypedArray<Item> Inventory::get_items() const
{ 
    return items; 
}

void Inventory::set_slots(const TypedArray<Slot>& new_slots) 
{
    slots = new_slots;
}
TypedArray<Slot> Inventory::get_slots() const
{ 
    return slots; 
}