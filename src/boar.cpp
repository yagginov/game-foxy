#include "boar.h"

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

void Boar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_hit", "target_pos"), &Boar::_hit);
    
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &Boar::_damage);
	ClassDB::bind_method(D_METHOD("_dead"), &Boar::_dead);

    ClassDB::bind_method(D_METHOD("_target_spotted", "target_pos"), &Boar::_target_spotted);
	ClassDB::bind_method(D_METHOD("_target_missed"), &Boar::_target_missed);

}

Boar::Boar() {
    state = States::idle;

    v_states.push_back(new State(0.0));     // idle
    v_states.push_back(new State(5.0));     // run
    v_states.push_back(new State(2.0));     // stun

    direction = Vector2(0.0, 0.0);

    health_label = nullptr;
}

Boar::~Boar() {
    // Add your cleanup here.
    for (auto& it : v_states)
	{
		delete(it);
	}
}

void Boar::_ready() {
    add_to_group("Enemy");
    
    health_label = get_node<Label>("HealthLabel");

    components = get_node<ComponentsContainer>("ComponentsContainer");
	components->bind(this);
}

void Boar::_physics_process(double delta) {
    switch(state)
    {
    case States::idle:
        f_idle(delta);
        break;
    case States::run:
        f_run(delta);
        break;
    case States::stun:
        f_stun(delta);
        break;
    }

    if(health_label)
    {
        health_label->set_text(String::num(components->health->get_hp()));
    }

    Actor::move(direction, delta);
}

void Boar::f_idle(double delta)
{
    
}

void Boar::f_run(double delta)
{
    if (v_states[state]->update(delta))
    {
        change_state(States::stun);
        return;
    }
}

void Boar::f_stun(double delta)
{
    if (v_states[state]->update(delta))
    {
        change_state(States::idle);
    }
    direction = Vector2(0.0, 0.0);
}

void Boar::_hit(Vector2 target_pos)
{
    _damage(target_pos);
    change_state(States::stun);
}

void Boar::_damage(Vector2 enemy_pos)
{
    double acc = get_acceleration();
    set_acceleration(1200);
    Actor::_damage(enemy_pos);
    set_acceleration(acc);
}

void Boar::_dead()
{
    queue_free();
}

void Boar::_target_spotted(Vector2 target_pos)
{
    if (state == States::idle)
    {
        change_state(States::run);
    }
    else if (state == States::run)
    {
        direction = (target_pos - get_position()).normalized();
    }
}

void Boar::_target_missed()
{
    change_state(States::idle);
    direction = Vector2(0.0, 0.0);
}

void Boar::change_state(States p_state)
{
	v_states[state]->reset();
	state = p_state;
}