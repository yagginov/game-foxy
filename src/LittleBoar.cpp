#include "LittleBoar.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>

using namespace godot;

void LittleBoar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_detection_area_entered", "area"), &LittleBoar::_on_detection_area_entered);
    ClassDB::bind_method(D_METHOD("_on_detection_area_exited", "area"), &LittleBoar::_on_detection_area_exited);
        
    ClassDB::bind_method(D_METHOD("_give_damage", "area"), &LittleBoar::_give_damage);

}

LittleBoar::LittleBoar() {
    detection_area = nullptr;
    ray_cast = nullptr;
    target = nullptr;
    healthLabel = nullptr;
    set_hp(2.0);
    set_speed(6.0);
    set_attack(2.0);

    state = States::idle;

    stun_time = 0.0;
    run_time = 0.0;
    direction = Vector2(0.0, 0.0);
    knockback_time = 0.0;
}

LittleBoar::~LittleBoar() {
}

void LittleBoar::_ready() {
    add_to_group("Enemy");

    detection_area = get_node<Area2D>("SearchArea");
    ray_cast = get_node<RayCast2D>("RayCast2D");
    if (ray_cast)
    {
        ray_cast->set_collide_with_bodies(false);
        ray_cast->set_collide_with_areas(true);
    }
    
    healthLabel = get_node<Label>("HealthLabel");

    hit_box = get_node<Area2D>("HitBox");
    
    detection_area->connect("area_entered", Callable(this, "_on_detection_area_entered"));
    detection_area->connect("area_exited", Callable(this, "_on_detection_area_exited"));

    hit_box->connect("area_entered", Callable(this, "_give_damage"));
}

void LittleBoar::_physics_process(double delta) {
    switch(state)
    {
    case States::idle:
        idle(delta);
        break;
    case States::run:
        run(delta);
        break;
    case States::stun:
        stun(delta);
        break;
    case States::dead:
        dead(delta);
        break;

    default:
        break;
    }

    if(healthLabel)
    {
        healthLabel->set_text(String::num(hp));
    }    

    if (knockback_time > 0.0)
    {
        knockback = -direction * pixels_in_meter * speed * 1.5 * (knockback_time / 0.4);
        set_velocity(knockback);
        move_and_slide();

        knockback_time -= delta;
        if (knockback_time < 0.0) { knockback_time = 0.0; }
    }
}

void LittleBoar::idle(double delta)
{
    if (is_collided_player()) { state = States::run; run_time = 20.0 / 6.0; } 
}

void LittleBoar::run(double delta)
{
    run_time -= delta;

    if (run_time < 0.0) { state = States::stun; stun_time = 3.0; }

    if (is_collided_player())
    {
        direction = (target->get_global_position() - get_global_position()).normalized();
        // movement
        set_velocity(direction * speed * pixels_in_meter);
        move_and_slide();
    }
    else { state = States::idle; }
}

void LittleBoar::stun(double delta)
{
    stun_time -= delta;
    if (stun_time < 0.0) { state = States::idle; }
}

void LittleBoar::dead(double delta)
{
    queue_free();
}

bool LittleBoar::is_collided_player()
{
    if (target)
    {
        ray_cast->set_target_position(target->get_node<Area2D>("HurtBox")->get_global_position() - get_global_position());
        if (ray_cast->is_colliding())
        {
            Node *collider = Object::cast_to<Node>(ray_cast->get_collider());  
            collider = Object::cast_to<Node>(collider->get_parent());
            return collider == target;
        }
    }
    return false;
}

void LittleBoar::_on_detection_area_entered(Node *area) {
    area = Object::cast_to<Node>(area->get_parent());

    if (area->is_in_group("Player")) {
        target = cast_to<Node2D>(area);
        ray_cast->set_target_position(target->get_global_position());
        if (is_collided_player()) { state = States::run; run_time = 20.0 / 6.0; }
    }
}

void LittleBoar::_on_detection_area_exited(Node *area) {
    area = Object::cast_to<Node>(area->get_parent());
    if (area == target) {
        target = nullptr;
        state = States::idle;
    }
}

void LittleBoar::_give_damage(Node2D *area)
{
    area = Object::cast_to<Node2D>(area->get_parent());
    if (area->is_in_group("Player")) {
        area->call("take_damage", 2, direction);
        state = States::stun; stun_time = 3.0;
    }
}

void LittleBoar::take_damage(int amount) {
    hp -= amount;
    knockback_time = 0.4;
    if (hp <= 0.1) {
        hp = 0;
        state = States::dead;
        queue_free();
    }
}