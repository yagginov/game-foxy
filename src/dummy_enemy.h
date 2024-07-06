#ifndef DUMMY_ENEMY_H
#define DUMMY_ENEMY_H

#include <godot_cpp/classes/label.hpp>

#include "actor.h"
#include "components/animation_controller.h"
#include "components/health_component.h"
#include "components/hurtbox.h"

namespace godot {

class DummyEnemy : public Actor {
    GDCLASS(DummyEnemy, Actor)

protected:
    static void _bind_methods();

private:
    Label* health_label;

    AnimationController* animation_controller;
    HealthComponent* health;
    Hurtbox* hurtbox;

public:
    DummyEnemy();
    ~DummyEnemy();

    void _ready();
    void _process(double delta) override;
    void _physics_process(double delta) override;

    void _damage(Vector2 enemy_pos) override;
    void _dead();
};

}

#endif
