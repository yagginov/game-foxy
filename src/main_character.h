#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "actor.h"
#include "state.h"
#include "animation_controller.h"

namespace godot {

class MainCharacter : public Actor {
	GDCLASS(MainCharacter, Actor)


enum States
{
	idle = 0,
	run = 1,
	slide = 2
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

public:	


public:
	MainCharacter();
	~MainCharacter();

    void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void f_idle(double delta);
	void f_run(double delta);
	void f_slide(double delta);

	void change_state(States state);

};

}	// namespace godot

#endif	// MAIN_CHARACTER_H