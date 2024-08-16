#ifndef ITEM_H
#define ITEM_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/variant/string.hpp>

#include "game_manager.h"

namespace godot {

class Item : public Node2D 
{
    GDCLASS(Item, Node2D);

protected:
    static void _bind_methods();

private:
    String name;
    Texture2D* texture;
    
protected:
    GameManager* gm;

public:
    Item();
    ~Item();

    void _ready() override;
    void _physics_process(double delta) override;

    virtual void use_item();

    void set_name(const String p_name);
    String get_name() const;

    void set_texture(Texture2D* p_texture);
    Texture2D* get_texture() const;

};

}           // namespace godot

#endif      // ITEM_H
