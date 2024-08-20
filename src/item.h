#ifndef ITEM_H
#define ITEM_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "game_manager.h"

namespace godot {

class Item : public Resource 
{
    GDCLASS(Item, Resource);

protected:
    static void _bind_methods();

private:
    String name;
    Ref<Texture2D> texture;
    
protected:
    GameManager* gm;

public:
    Item();
    ~Item();

    virtual void use_item();

    void set_name(const String p_name);
    String get_name() const;

    void set_texture(const Ref<Texture2D>& p_texture);
    Ref<Texture2D> get_texture() const;

};

}           // namespace godot

#endif      // ITEM_H
