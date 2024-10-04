#include "dummy_enemy.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void DummyEnemy::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &DummyEnemy::_damage);
}

DummyEnemy::DummyEnemy() 
{
    
}

DummyEnemy::~DummyEnemy() 
{

}

void DummyEnemy::_ready() 
{
    health_label = get_node<Label>("HealthLabel");

    animation_controller = get_node<AnimationController>("AnimationController");
	hurtbox = get_node<Hurtbox>("Hurtbox");
	health = get_node<HealthComponent>("HealthComponent");

	hurtbox->connect("damage", Callable(this, "_damage"));
	health->connect("dead", Callable(this, "_dead"));
}

void DummyEnemy::_process(double delta) {
    
}

void DummyEnemy::_physics_process(double delta)
{
    if (health_label) {
        health_label->set_text(String::num(health->get_hp()));
    }

    if (!animation_controller->is_playing())
    {
        animation_controller->set_state(0);
        animation_controller->play_current_animation();
    }
}


void DummyEnemy::_damage(Vector2 enemy_pos)
{
	animation_controller->set_state(1);
    animation_controller->play_current_animation();
}

void DummyEnemy::_dead()
{

}

Dictionary DummyEnemy::save()
{
    Dictionary info;
    info ["hp"] = health->get_hp();
    return info;
}

void DummyEnemy::load(const Dictionary& info)
{
    if (info.has("hp"))
    {
        health->set_hp(info["hp"]);
    }
}