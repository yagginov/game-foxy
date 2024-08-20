#ifndef INVENTORY_H
#define INVENTORY_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "game_manager.h"
#include "slot.h"
#include "item.h"

namespace godot {

class Inventory : public Node2D 
{
    GDCLASS(Inventory, Node2D);

protected:
    static void _bind_methods();

private:
    TypedArray<Item> items;
    TypedArray<Slot> slots;
    TypedArray<NodePath> slots_path;
    Ref<Item> active_item;

protected:
    GameManager* gm;

public:
    Inventory();
    ~Inventory();

    void _ready() override;
    void _physics_process(double delta) override;

    void update();
    void update_slots();

    void use_active_item();
    void set_active_item(size_t index);

    // Setters
    void set_items(const TypedArray<Item>& new_items);
    void set_slots(const TypedArray<NodePath>& new_slots);

    // Getters
    TypedArray<Item> get_items() const;
    TypedArray<NodePath> get_slots() const;

};          // class Inventory

}           // namespace godot

#endif      // INVENTORY_H
