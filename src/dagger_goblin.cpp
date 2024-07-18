#include "dagger_goblin.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

void DaggerGoblin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_hit", "target_pos"), &DaggerGoblin::_hit);
    ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &DaggerGoblin::_damage);
	ClassDB::bind_method(D_METHOD("_dead"), &DaggerGoblin::_dead);

    ClassDB::bind_method(D_METHOD("_target_spotted", "target_pos"), &DaggerGoblin::_target_spotted);
	ClassDB::bind_method(D_METHOD("_target_missed"), &DaggerGoblin::_target_missed);

}

DaggerGoblin::DaggerGoblin() {
    state = States::idle;

    v_states.push_back(new State(0.0));     // idle
    v_states.push_back(new State(1.0));     // run
    v_states.push_back(new State(2.0));     // attack

    direction = Vector2(0.0, 0.0);

    health_label = nullptr;
    components = nullptr;

    target_distance = 0.0;
}

DaggerGoblin::~DaggerGoblin() {
    // Add your cleanup here.
    for (auto& it : v_states)
	{
		delete(it);
	}
}

void DaggerGoblin::_ready() {
    add_to_group("Enemy");
    
    health_label = get_node<Label>("HealthLabel");

    components = get_node<ComponentsContainer>("ComponentsContainer");
    components->_ready();
	components->bind(this);

    if (components->hitbox)
    {
        //UtilityFunctions::print(components->hitbox);
        components->hitbox->turn_off();
    }
    
}

void DaggerGoblin::_physics_process(double delta) {
    
    double angle = -direction.angle_to(Vector2(1.0, 0.0));
    if (components->hitbox)
    {
        components->hitbox->set_rotation(angle);
    }
    
    switch(state)
    {
    case States::idle:
        f_idle(delta);
        break;
    case States::run:
        f_run(delta);
        break;
    case States::attack:
        f_attack(delta);
        break;
    }

    if(health_label)
    {
        health_label->set_text(String::num(components->health->get_hp()));
    }

    Actor::move(direction, delta);
}

void DaggerGoblin::f_idle(double delta)
{
    if (v_states[state]->is_start())
    {
        if (components->hitbox)
        {
            components->hitbox->turn_off();
        }
    }
}

void DaggerGoblin::f_run(double delta)
{
    if (!v_states[state]->update(delta))
    {
        return;
    }

    if (target_distance < 25)
    {
        change_state(States::attack);
    }
}

void DaggerGoblin::f_attack(double delta)
{
    if (v_states[state]->is_start())
	{
		if (components->hitbox)
        {
            components->hitbox->turn_on();
        }
	}

    if (v_states[state]->update(delta))
	{
		if (components->hitbox)
        {
            components->hitbox->turn_off();
        }
		change_state(States::idle);
	}
    set_velocity(Vector2(0.0, 0.0));
    direction = Vector2(0.0, 0.0);
}

void DaggerGoblin::_hit(Vector2 target_pos)
{

}

void DaggerGoblin::_damage(Vector2 enemy_pos)
{
    double acc = get_acceleration();
    set_acceleration(300);
    Actor::_damage(enemy_pos);
    set_acceleration(acc);
}

void DaggerGoblin::_dead()
{
    queue_free();
}

void DaggerGoblin::_target_spotted(Vector2 target_pos)
{
    direction = target_pos - get_position();
    target_distance = direction.length();
    //UtilityFunctions::print(String("target distance = ") + String::num(target_distance));
    direction = direction.normalized();
    if (state != States::attack)
    {
        change_state(States::run);
    }
}

void DaggerGoblin::_target_missed()
{
    change_state(States::idle);
    direction = Vector2(0.0, 0.0);
}

void DaggerGoblin::change_state(States p_state)
{
    if (state == p_state)
    {
        return;
    }
	v_states[state]->reset();
	state = p_state;
}