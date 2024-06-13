#ifndef LITTLE_BOAR_H
#define LITTLE_BOAR_H

#include "BaseEnemy.h"

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

namespace godot {

enum States{
    idle,
    run,
    stun,
    dead
};

class LittleBoar : public BaseEnemy {
    GDCLASS(LittleBoar, BaseEnemy);

private:
    Area2D *detection_area;
    Area2D *hit_box;
    RayCast2D *ray_cast;
    Node2D *target;
    Label *healthLabel;

    States state;

    double stun_time;
    double run_time;

    Vector2 direction;
protected:
    static void _bind_methods();

public:
    LittleBoar();
    ~LittleBoar();

    void take_damage(int amount) override;

    void _ready() override;
    void _physics_process(double delta) override;
    void _on_detection_area_entered(Node *area);
    void _on_detection_area_exited(Node *area);

    void _give_damage(Node2D *area);

    void idle(double delta);
    void run(double delta);
    void stun(double delta);
    void dead(double delta);

private:
    bool is_collided_player();
};

}

#endif // LITTLE_BOAR_H
