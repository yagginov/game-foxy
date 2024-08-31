#ifndef LIFTABLE_OBJECT_H
#define LIFTABLE_OBJECT_H

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "components/search_area.h"
#include "components/velocity_component.h"
#include "item.h"

namespace godot {

class LiftableObject : public CharacterBody2D {
    GDCLASS(LiftableObject, CharacterBody2D);

protected:
    static void _bind_methods();

private:
    NodePath sprite_path;
    Sprite2D* sprite;
    NodePath search_area_path;
    SearchArea* search_area;
    Ref<Item> item;

    bool is_allowed;

    Ref<VelocityComponent> velocity_component;

public:
    LiftableObject();
    LiftableObject(const Ref<Item>& p_item);
    ~LiftableObject();

    void _ready() override;
    void _physics_process(double delta) override;

    void _target_spotted(Vector2 target_pos);
    void _target_missed();

    void set_search_area_path(const NodePath& p_search_area_path);
    NodePath get_search_area_path() const;

    void set_sprite_path(const NodePath& p_sprite_path);
    NodePath get_sprite_path() const;

    void set_item(const Ref<Item>& p_item);
    Ref<Item> get_item() const;

    void set_velocity_component(const Ref<VelocityComponent>& p_velocity_component);
    Ref<VelocityComponent> get_velocity_component() const;

};

}       // namespace godot

#endif // LIFTABLE_OBJECT_H
