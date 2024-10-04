#ifndef DAGGER_GOBLIN_H
#define DAGGER_GOBLIN_H

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/label.hpp>

#include "actor.h"
#include "components_container.h"
#include "state.h"

namespace godot {

class DaggerGoblin : public Actor {
    GDCLASS(DaggerGoblin, Actor);

enum States{
    idle = 0,
    run,
    attack,
    attack_cooldown
};

protected:
    static void _bind_methods();

private:
    States state;
    Vector<State*> v_states;

    Vector2 direction;

    Label *health_label;
    ComponentsContainer* components;

    double target_distance;

public:
    DaggerGoblin();
    ~DaggerGoblin();

    void _ready() override;
    void _physics_process(double delta) override;

    void f_idle(double delta);
    void f_run(double delta);
    void f_attack(double delta);
    void f_attack_cooldown(double delta);

    void _hit(Vector2 target_pos);
    void _damage(Vector2 enemy_pos) override;
    void _dead() override;

    void _target_spotted(Vector2 enemy_pos);
    void _target_missed();

    void change_state(States state);

    Dictionary save() override;
    void load(const Dictionary& info) override;

};

}       // namespace godot

#endif // DAGGER_GOBLIN_H
