#ifndef OBJECT_H
#define OBJECT_H

#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {

class Object : public AnimatedSprite2D {
    GDCLASS(Object, AnimatedSprite2D);

protected:
    static void _bind_methods();

private:
    ComponentsContainer* components;

public:
    Object();
    ~Object();

    void _ready() override;
    void _physics_process(double delta) override;

    void _damage(Vector2 enemy_pos);

};

}           // namespace godot

#endif      // OBJECT_H
