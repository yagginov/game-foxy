#ifndef DUMMY_ENEMY_H
#define DUMMY_ENEMY_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot {

class DummyEnemy : public Area2D {
    GDCLASS(DummyEnemy, Area2D)

private:
    Label* health_label;
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
