#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "actor.h"
#include "state.h"
#include "animation_controller.h"
#include "health_component.h"
#include "hurtbox.h"
#include "hitbox.h"

namespace godot {

class MainCharacter : public Actor {
	GDCLASS(MainCharacter, Actor)


enum States
{
	idle = 0,
	run = 1,
	slide = 2,
	attack = 3
};

const Vector2 VECTOR2_ZERO = Vector2(0.0, 0.0);

protected:
	static void _bind_methods();

private:
	Input* i;
	Vector2 direction;

	States state;
	Vector<State*> v_states;

	AnimationController* animation_controller;

	Hurtbox* hurtbox;
	Hitbox* hitbox;
	HealthComponent* health;

public:
	MainCharacter();
	~MainCharacter();

    void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void f_idle(double delta);
	void f_run(double delta);
	void f_slide(double delta);
	void f_attack(double delta);

	void _damage(Vector2 enemy_pos);
	void _dead();

	void change_state(States state);

};

}	// namespace godot

#endif	// MAIN_CHARACTER_H