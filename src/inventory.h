#ifndef INVENTORY_H
#define INVENTORY_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "game_manager.h"
#include "item.h"
#include "slot.h"

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

private:
// temp
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

    void update_slots();

    void use_active_item();

    
    // set / get
    void set_slots(const TypedArray<NodePath>& new_slots);
    TypedArray<NodePath> get_slots() const;

    Dictionary save();


};          // class Inventory

}           // namespace godot

#endif      // INVENTORY_H
