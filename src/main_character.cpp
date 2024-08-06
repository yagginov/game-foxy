#include "main_character.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

#define PI 3.1415926535897932384626433832795

void MainCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &MainCharacter::_damage);
	ClassDB::bind_method(D_METHOD("_dead"), &MainCharacter::_dead);
	ClassDB::bind_method(D_METHOD("_hit", "target_pos"), &MainCharacter::_hit);
}

MainCharacter::MainCharacter() {
	// Initialize any variables here.	
	i = Input::get_singleton();

	direction = VECTOR2_ZERO;

	state = States::idle;

	v_states.push_back(new State(0.0));
	v_states.push_back(new State(0.0));
	v_states.push_back(new State(0.2));
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

	components = get_node<ComponentsContainer>("ComponentsContainer");

	components->bind(this);

	components->hitbox->turn_off();

	sword = get_node<Sprite2D>("Sword");
}

void MainCharacter::_process(double delta) {

}

void MainCharacter::_physics_process(double delta) 
{
	direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down").normalized();

	components->animation_controller->set_angle(direction);
	components->animation_controller->play_current_animation();

	double angle = -components->animation_controller->get_angle_vector().angle_to(Vector2(1.0, 0.0));
	components->hitbox->set_rotation(angle);


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

	case States::attack :
		f_attack(delta);
		break;
	}

	move(direction, delta);
}


void MainCharacter::f_idle(double delta)
{
	if (v_states[state]->is_start())
	{
		components->hitbox->turn_off();
		sword->set_visible(false);
	}

	if (direction != VECTOR2_ZERO)
	{
		change_state(States::run);
	}

	if (i->is_action_just_pressed("ui_accept"))
	{
		change_state(States::slide);
	}

	if (i->is_action_just_pressed("ui_select"))
	{
		change_state(States::idle);
		state = States::attack;
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

	if (i->is_action_just_pressed("ui_select"))
	{
		change_state(States::idle);
		state = States::attack;
	}
}

void MainCharacter::f_slide(double delta)
{
	if (v_states[state]->is_start())
	{
		velocity = components->animation_controller->get_angle_vector() * 0.2 * get_acceleration();
		set_velocity(velocity);
	}

	if (v_states[state]->update(delta))
	{
		change_state(States::idle);
	}
	direction = VECTOR2_ZERO;
}

void MainCharacter::f_attack(double delta)
{
	if (v_states[state]->is_start())
	{
		components->hitbox->turn_on();
		sword->set_visible(true);
		double angle = -components->animation_controller->get_angle_vector().angle_to(Vector2(1.0, 0.0));
		sword->set_rotation(angle);
	}
	else
	{
		sword->set_rotation(sword->get_rotation() + PI * ( delta / 0.2));
	}

	if (v_states[state]->update(delta))
	{
		components->hitbox->turn_off();
		change_state(States::idle);
		sword->set_visible(false);
	}
	
	direction = VECTOR2_ZERO;
}

void MainCharacter::_damage(Vector2 enemy_pos)
{
	Actor::_damage(enemy_pos);
	change_state(States::idle);
}

void MainCharacter::_dead()
{
	//UtilityFunctions::print("U are dead");
}

void MainCharacter::_hit(Vector2 target_pos)
{
	//UtilityFunctions::print("HIT");
}

void MainCharacter::change_state(States p_state)
{
	v_states[state]->reset();
	state = p_state;

	components->animation_controller->set_state(static_cast<int>(state));
}
