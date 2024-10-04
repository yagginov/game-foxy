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
    size_t max_count;

    String resource_path;
    
protected:
    GameManager* gm;

public:
    Item();
    Item(const Item& other);
    ~Item();

    virtual bool use_item();

    void set_name(const String p_name);
    String get_name() const;

    void set_texture(const Ref<Texture2D>& p_texture);
    Ref<Texture2D> get_texture() const;

    void set_max_count(const size_t p_max_count);
    size_t get_max_count() const;

    void set_resource_path(const String p_resource_path);
    String get_resource_path() const;

};

inline bool operator==(const Item& lhs, const Item& rhs) 
{ 
    return lhs.get_name() == rhs.get_name();
}

}           // namespace godot

#endif      // ITEM_H
