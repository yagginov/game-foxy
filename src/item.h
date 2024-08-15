#ifndef ITEM_H
#define ITEM_H

#include <godot_cpp/classes/node2d.hpp>

#include "game_manager.h"

namespace godot {

class Item : public Node2D 
{
    GDCLASS(Item, Node2D);

protected:
    static void _bind_methods();

private:

protected:
    GameManager* gm;

public:
    Item();
    ~Item();

    void _ready() override;
    void _physics_process(double delta) override;

    virtual void use_item();

};

}           // namespace godot

#endif      // ITEM_H
