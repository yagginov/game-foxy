#include "inventory.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "liftable_object.h"
#include "main_character.h"
#include "components/velocity_component.h"

using namespace godot;

void Inventory::_bind_methods() 
{    
    ClassDB::bind_method(D_METHOD("set_slots", "slots"), &Inventory::set_slots);
    ClassDB::bind_method(D_METHOD("get_slots"), &Inventory::get_slots);
    ADD_PROPERTY(PropertyInfo(
            Variant::ARRAY, 
            "slots", 
            PROPERTY_HINT_ARRAY_TYPE, 
            String::num(Variant::NODE_PATH) + "/" + String::num(PROPERTY_HINT_NODE_PATH_TO_EDITED_NODE) + String(":") + Slot::get_class_static()), 
        "set_slots", 
        "get_slots");  
         
    ClassDB::bind_method(D_METHOD("update_slots"), &Inventory::update_slots);

}

Inventory::Inventory() 
{
    gm = nullptr;

    // temp
    was_key_q_pressed = false;
    // temp

    active_item_index = 0;
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
    if (gm->i->is_physical_key_pressed(KEY_Q) && !was_key_q_pressed)
    {
        use_active_item();
    }
    was_key_q_pressed = gm->i->is_physical_key_pressed(KEY_Q);
    
}

bool Inventory::add_item(Ref<Item> new_item)
{
    Slot* empty_slot = nullptr;
    size_t count = 1;
    for (int i = 0; i < slots.size() - 1; ++i)
    {
        Slot* slot = Object::cast_to<Slot>(slots[i]);

        if (slot->is_empty())
        {
            if (!empty_slot)
            {
                empty_slot = slot;
            }
        }
        else
        {
            if (slot->get_item()->get_name() == new_item->get_name())
            {
                if (slot->add_item(count))
                {   
                    //slot->set_item(slot->get_item());
                    slot->update();
                    return true;
                }
            }
        }
    }
    if (empty_slot)
    {
        empty_slot->set_item(new_item);
        return true;
    }

    return false;
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

void Inventory::use_active_item()
{
    Slot* active_slot = Object::cast_to<Slot>(slots[slots.size() - 1]);
    if (!active_slot->is_empty())
    {
        active_slot->set_item_count(active_slot->get_item_count() - (int)active_slot->get_item()->use_item());
        if (!active_slot->get_item_count())
        {
            active_slot->set_item(nullptr);
        }
    }
}

void Inventory::set_slots(const TypedArray<NodePath>& new_slots) 
{
    slots_path = new_slots;
}
TypedArray<NodePath> Inventory::get_slots() const
{ 
    return slots_path; 
}
