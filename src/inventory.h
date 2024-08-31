#ifndef INVENTORY_H
#define INVENTORY_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "game_manager.h"
#include "slot.h"
#include "item.h"

namespace godot {

class Inventory : public Control
{
    GDCLASS(Inventory, Control);

protected:
    static void _bind_methods();

private:
    TypedArray<Slot> slots;
    TypedArray<NodePath> slots_path;
    size_t active_item_index;

    Slot* from_slot;
    Ref<Item> item;

    Sprite2D* drag_sprite;

private:
// temp
    bool was_key_1_pressed;
    bool was_key_2_pressed;
    bool was_key_3_pressed;
    bool was_key_4_pressed;
    bool was_key_5_pressed;
    bool was_key_q_pressed;
// temp

protected:
    GameManager* gm;

public:
    Inventory();
    ~Inventory();

    void _ready() override;
    void _physics_process(double delta) override;

    bool add_item(Ref<Item> new_item);

    void update();
    void update_slots();

    void use_active_item();
    void set_active_item(size_t index);

    void _on_start_dragging(Slot* from_slot, Ref<Item> item);
    void _on_end_dragging(Slot* to_slot);
    
    // set / get
    void set_slots(const TypedArray<NodePath>& new_slots);
    TypedArray<NodePath> get_slots() const;


};          // class Inventory

}           // namespace godot

#endif      // INVENTORY_H
