#ifndef SLOT_H
#define SLOT_H

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/classes/label.hpp>

#include "item.h"

namespace godot {

class Slot : public Panel {
    GDCLASS(Slot, Panel)

protected:
    static void _bind_methods();

private:
    GameManager* gm;

    Sprite2D*           item_sprite;
    NodePath            item_sprite_path;
    Ref<Item>           item;
    Sprite2D*           background_sprite;

    Label*              count_label;

    size_t              item_count;

public:
    Slot();
    ~Slot();

    void _ready();
    void _physics_process(double delta) override;

    void _gui_input(Ref<InputEvent> event);
    void _mouse_entered();
    void _mouse_exited();

    void update();

    bool add_item(size_t& count);

    void set_item_texture(const Ref<Texture2D>& p_texture);
    bool is_empty() const;

    // set / get
    void            set_item_sprite(const NodePath& p_item_sprite_path);
    NodePath        get_item_sprite() const;

    void set_item(const Ref<Item>& p_item);
    Ref<Item> get_item() const;

    void set_item_count(const size_t p_item_count);
    size_t get_item_count() const;
    

};          // class Slot

}           // namespace godot

#endif      // SLOT_H
