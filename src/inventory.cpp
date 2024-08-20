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
            PROPERTY_HINT_ARRAY_TYPE, 
            String::num(Variant::NODE_PATH) + "/" + String::num(PROPERTY_HINT_NODE_PATH_TO_EDITED_NODE) + String(":") + Slot::get_class_static()), 
        "set_slots", 
        "get_slots");  
         

    ClassDB::bind_method(D_METHOD("update"), &Inventory::update);
    ClassDB::bind_method(D_METHOD("update_slots"), &Inventory::update_slots);

}

Inventory::Inventory() 
{
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

    update_slots();
}

void Inventory::_physics_process(double delta) 
{
    update();
}


void Inventory::update()
{
    if (slots.size() != items.size())
    {
        return;
    }
    for (int i = 0; i < items.size(); ++i)
    {
        Ref<Item> item = Object::cast_to<Item>(items[i]);
        Slot* slot = Object::cast_to<Slot>(slots[i]);

        if (item.is_valid())
        {  
            if (slot)
            {
                slot->set_item_texture(item->get_texture());
            }            
        }
        else
        {
            if (slot)
            {
                slot->set_item_texture(nullptr);
            } 
        }
    }
}

void Inventory::update_slots()
{
    slots.resize(slots_path.size());
    for (int i = 0; i < slots_path.size(); ++i)
    {
        if (has_node(slots_path[i]))
        {
            slots[i] = get_node<Slot>(slots_path[i]);
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

void Inventory::set_slots(const TypedArray<NodePath>& new_slots) 
{
    slots_path = new_slots;
    update_slots();
}
TypedArray<NodePath> Inventory::get_slots() const
{ 
    return slots_path; 
}