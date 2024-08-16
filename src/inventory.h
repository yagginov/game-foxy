#ifndef INVENTORY_H
#define INVENTORY_H

#include <godot_cpp/classes/node2d.hpp>

#include "game_manager.h"

namespace godot {

class Inventory : public Node2D 
{
    GDCLASS(Inventory, Node2D);

protected:
    static void _bind_methods();

private:

protected:
    GameManager* gm;

public:
    Inventory();
    ~Inventory();

    void _ready() override;
    void _physics_process(double delta) override;

};          // class Inventory

}           // namespace godot

#endif      // INVENTORY_H
