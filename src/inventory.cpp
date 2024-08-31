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
         

    ClassDB::bind_method(D_METHOD("update"), &Inventory::update);
    ClassDB::bind_method(D_METHOD("update_slots"), &Inventory::update_slots);

    ClassDB::bind_method(D_METHOD("_on_start_dragging", "from_slot", "item"), &Inventory::_on_start_dragging);
    ClassDB::bind_method(D_METHOD("_on_end_dragging", "to_slot"), &Inventory::_on_end_dragging);

}

Inventory::Inventory() 
{
    gm = nullptr;

    // temp
    was_key_1_pressed = false;
    was_key_2_pressed = false;
    was_key_3_pressed = false;
    was_key_4_pressed = false;
    was_key_5_pressed = false;
    was_key_q_pressed = false;
    // temp

    active_item_index = 0;

    drag_sprite = memnew(Sprite2D);
}

Inventory::~Inventory() 
{
    // Add your cleanup here.
}

void Inventory::_ready() 
{
    add_child(drag_sprite);
    drag_sprite->set_centered(true);
    drag_sprite->set_z_index(1);

    add_to_group("UI");

    gm = GameManager::get_singleton();

    update_slots();
}

void Inventory::_physics_process(double delta) 
{
    if (item.is_valid())
    {
        drag_sprite->set_global_position(gm->mc->get_mouse_position());
        gm->set_input_allowed(false);

        if (gm->i->is_physical_key_pressed(KEY_R))
        {
            Vector2 direction = (gm->mc->get_mouse_position() - gm->mc->get_global_position()).normalized();

            gm->spawn_liftable_object(item, gm->mc->get_global_position(), direction * 50, "res://resources/drop_item_velocity_component.tres");

            from_slot = nullptr;
            drag_sprite->set_texture(nullptr);
            gm->set_input_allowed(true);
        }
    }

    if (gm->i->is_physical_key_pressed(KEY_1) && !was_key_1_pressed)
    {
        set_active_item(0);
    }
    was_key_1_pressed = gm->i->is_physical_key_pressed(KEY_1);

    if (gm->i->is_physical_key_pressed(KEY_2) && !was_key_2_pressed)
    {
        set_active_item(1);
    }
    was_key_2_pressed = gm->i->is_physical_key_pressed(KEY_2);

    if (gm->i->is_physical_key_pressed(KEY_3) && !was_key_3_pressed)
    {
        set_active_item(2);
    }
    was_key_3_pressed = gm->i->is_physical_key_pressed(KEY_3);

    if (gm->i->is_physical_key_pressed(KEY_4) && !was_key_4_pressed)
    {
        set_active_item(3);
    }
    was_key_4_pressed = gm->i->is_physical_key_pressed(KEY_4);

    if (gm->i->is_physical_key_pressed(KEY_5) && !was_key_5_pressed)
    {
        set_active_item(4);
    }
    was_key_5_pressed = gm->i->is_physical_key_pressed(KEY_5);


    if (gm->i->is_physical_key_pressed(KEY_Q) && !was_key_q_pressed)
    {
        use_active_item();
    }
    was_key_q_pressed = gm->i->is_physical_key_pressed(KEY_Q);
    
}

bool Inventory::add_item(Ref<Item> new_item)
{
    for (int i = 0; i < slots.size() - 1; ++i)
    {
        Slot* slot = Object::cast_to<Slot>(slots[i]);

        if (slot->is_empty())
        {
            slot->set_item(new_item);
            return true;
        }
    }
    return false;
}


void Inventory::update()
{
    
}

void Inventory::update_slots()
{
    slots.resize(slots_path.size());
    for (int i = 0; i < slots_path.size(); ++i)
    {
        if (has_node(slots_path[i]))
        {
            Slot* slot = get_node<Slot>(slots_path[i]);

            if (i < slots_path.size() - 1)
            {
                slot->connect("start_drag", Callable(this, "_on_start_dragging"));
                slot->connect("end_drag", Callable(this, "_on_end_dragging"));
            }
            
            slots[i] = slot;
        }
    }
}

void Inventory::_on_start_dragging(Slot* p_from_slot, Ref<Item> p_item)
{
    if (item.is_valid())
    {
        _on_end_dragging(p_from_slot);
        return;
    }

    item = p_item;
    from_slot = p_from_slot;
    from_slot->set_item(nullptr);
    drag_sprite->set_texture(this->item->get_texture());
}
void Inventory::_on_end_dragging(Slot* to_slot)
{
    if (item.is_null())
    {
        return;
    }

    if (!to_slot->is_empty())
    {
        from_slot->set_item(to_slot->get_item());
    }
    to_slot->set_item(item);

    from_slot = nullptr;
    item.unref();
    drag_sprite->set_texture(nullptr);
}

void Inventory::set_active_item(size_t index)
{
    if (index < slots.size() - 1)
    {
        Slot* slot = Object::cast_to<Slot>(slots[index]);
        Slot* active_slot = Object::cast_to<Slot>(slots[slots.size() - 1]);

        if (!slot->is_empty())
        {
            active_slot->set_item(slot->get_item());
            active_item_index = index;
        }
        else
        {
            active_slot->set_item(nullptr);
        }
    }
}

void Inventory::use_active_item()
{
    Slot* active_slot = Object::cast_to<Slot>(slots[slots.size() - 1]);
    if (!active_slot->is_empty())
    {
        active_slot->get_item()->use_item();
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
