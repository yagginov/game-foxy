#ifndef DUMMY_ENEMY_H
#define DUMMY_ENEMY_H

#include <godot_cpp/classes/animatable_body2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {

class DummyEnemy : public AnimatableBody2D {
    GDCLASS(DummyEnemy, AnimatableBody2D)

private:
    Label* health_label;
    AnimatedSprite2D* animatedSprite;
    int hp;

protected:
    static void _bind_methods();

public:
    DummyEnemy();
    ~DummyEnemy();

    void _ready();
    void _process(double delta);

    void take_damage(int amount);
};

}

#endif
