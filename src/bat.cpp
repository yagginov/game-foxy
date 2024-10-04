#include "bat.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

void Bat::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_hit", "target_pos"), &Bat::_hit);
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &Bat::_damage);
	ClassDB::bind_method(D_METHOD("_dead"), &Bat::_dead);

    ClassDB::bind_method(D_METHOD("_target_spotted", "target_pos"), &Bat::_target_spotted);
	ClassDB::bind_method(D_METHOD("_target_missed"), &Bat::_target_missed);

}

Bat::Bat() {
    state = States::idle;

    v_states.push_back(new State(0.0));     // idle
    v_states.push_back(new State(0.0));     // fly

    direction = Vector2(0.0, 0.0);

    health_label = nullptr;
}

Bat::~Bat() {
    // Add your cleanup here.
    for (auto& it : v_states)
	{
		delete(it);
	}
}

void Bat::_ready() {
    add_to_group("Enemy");
    
    health_label = get_node<Label>("HealthLabel");

    components = get_node<ComponentsContainer>("ComponentsContainer");
	components->bind(this);
}

void Bat::_physics_process(double delta) {
    switch(state)
    {
    case States::idle:
        f_idle(delta);
        break;
    case States::fly:
        f_fly(delta);
        break;
    }

    if(health_label)
    {
        health_label->set_text(String::num(components->health->get_hp()));
    }

    Actor::move(direction, delta);
}

void Bat::f_idle(double delta)
{
    
}

void Bat::f_fly(double delta)
{
    
}

void Bat::_hit(Vector2 target_pos)
{
    _damage(target_pos);
}

void Bat::_damage(Vector2 enemy_pos)
{
    double acc = get_acceleration();
    set_acceleration(500);
    Actor::_damage(enemy_pos);
    set_acceleration(acc);
}

void Bat::_dead()
{
    queue_free();
}

void Bat::_target_spotted(Vector2 target_pos)
{
    direction = (target_pos - get_position()).normalized();
}

void Bat::_target_missed()
{
    change_state(States::idle);
    direction = Vector2(0.0, 0.0);
}

void Bat::change_state(States p_state)
{
	v_states[state]->reset();
	state = p_state;
}

Dictionary Bat::save()
{
    Dictionary info;
    info["hp"] = components->health->get_hp();
    return info;
}