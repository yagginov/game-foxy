#include "LittleBoar.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>

void LittleBoar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_detection_area_entered", "area"), &LittleBoar::_on_detection_area_entered);
    ClassDB::bind_method(D_METHOD("_on_detection_area_exited", "area"), &LittleBoar::_on_detection_area_exited);
}

LittleBoar::LittleBoar() {
    detection_area = nullptr;
    ray_cast = nullptr;
    target = nullptr;
    healthLabel = nullptr;
    set_hp(2.0);
    set_speed(6.0);
    set_attack(2.0);
}

LittleBoar::~LittleBoar() {
}

void LittleBoar::_ready() {
    add_to_group("Enemy");

    detection_area = get_node<Area2D>("SearchArea");
    ray_cast = get_node<RayCast2D>("RayCast2D");
    if (ray_cast)
    {
        ray_cast->set_collide_with_areas(true);
        ray_cast->set_collide_with_bodies(false);
    }
    

    healthLabel = get_node<Label>("HealthLabel");
    
    detection_area->connect("area_entered", Callable(this, "_on_detection_area_entered"));
    detection_area->connect("area_exited", Callable(this, "_on_detection_area_exited"));
}

void LittleBoar::_physics_process(double delta) {
    if(healthLabel)
    {
        healthLabel->set_text(String::num(hp));
    }
    
    if (target)
    {
        ray_cast->set_target_position(target->get_global_position() - get_global_position());

        if (ray_cast->is_colliding())
        {
            Node *collider = Object::cast_to<Node>(ray_cast->get_collider());  
            collider = Object::cast_to<Node>(collider->get_parent());

            if (collider == target) {
                Vector2 direction = (target->get_global_position() - get_global_position()).normalized();
                // movement
                set_velocity(direction * speed * pixels_in_meter);
                move_and_slide();
            }
        }
    }
}

void LittleBoar::_on_detection_area_entered(Node *area) {
    area = Object::cast_to<Node>(area->get_parent());

    if (area->is_in_group("Player")) {
        target = cast_to<Node2D>(area);
        ray_cast->set_target_position(target->get_global_position());
    }
}

void LittleBoar::_on_detection_area_exited(Node *area) {
    area = Object::cast_to<Node>(area->get_parent());
    if (area == target) {
        target = nullptr;
    }
}

void LittleBoar::take_damage(int amount) {
    hp -= amount;
    if (hp <= 0) {
        hp = 0;
        queue_free();
    }
}