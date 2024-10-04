#ifndef BAT_H
#define BAT_H

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/label.hpp>

#include "actor.h"
#include "components_container.h"
#include "state.h"

namespace godot {

class Bat : public Actor {
    GDCLASS(Bat, Actor);

enum States{
    idle = 0,
    fly
};

protected:
    static void _bind_methods();

private:
    States state;
    Vector<State*> v_states;

    Vector2 direction;

    Label *health_label;
    ComponentsContainer* components;

public:
    Bat();
    ~Bat();

    void _ready() override;
    void _physics_process(double delta) override;

    void f_idle(double delta);
    void f_fly(double delta);

    void _hit(Vector2 target_pos);
    void _damage(Vector2 enemy_pos) override;
    void _dead();

    void _target_spotted(Vector2 enemy_pos);
    void _target_missed();

    void change_state(States state);

    Dictionary save() override;

};

}       // namespace godot

#endif // BAT_H
