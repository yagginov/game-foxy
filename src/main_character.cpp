#include "main_character.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;


void MainCharacter::_bind_methods() {
	
}

MainCharacter::MainCharacter() {
	// Initialize any variables here.	
	i = Input::get_singleton();

	direction = VECTOR2_ZERO;

	state = States::idle;

	v_states.push_back(new State(0.0));
	v_states.push_back(new State(0.0));
	v_states.push_back(new State(0.2));

}

MainCharacter::~MainCharacter() {
	// Add your cleanup here.
	for (auto& it : v_states)
	{
		delete(it);
	}
}

void MainCharacter::_ready() {
	add_to_group("Player");

	animation_controller = get_node<AnimationController>("AnimationController");
}

void MainCharacter::_process(double delta) {

}

void MainCharacter::_physics_process(double delta) 
{
	direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down").normalized();

	animation_controller->set_angle(direction);
	animation_controller->play_current_animation();

	switch(state)
	{
	case States::idle :
		f_idle(delta);
		break;

	case States::run :
		f_run(delta);
		break;

	case States::slide :
		f_slide(delta);
		break;
	}

	move(direction, delta);
}


void MainCharacter::f_idle(double delta)
{
	if (direction != VECTOR2_ZERO)
	{
		change_state(States::run);
	}

	if (i->is_action_just_pressed("ui_accept"))
	{
		change_state(States::slide);
	}
}

void MainCharacter::f_run(double delta)
{
	if (direction == VECTOR2_ZERO)
	{
		change_state(States::idle);
	}

	if (i->is_action_just_pressed("ui_accept"))
	{
		change_state(States::slide);
		return;
	}
}

void MainCharacter::f_slide(double delta)
{
	if (v_states[state]->is_start())
	{
		velocity = animation_controller->get_angle_vector() * 0.2 * get_acceleration();
		set_velocity(velocity);
	}

	if (v_states[state]->update(delta))
	{
		change_state(States::idle);
	}
}

void MainCharacter::change_state(States p_state)
{
	v_states[state]->reset();
	state = p_state;

	UtilityFunctions::print(p_state);

	animation_controller->set_state(static_cast<int>(state));
}
