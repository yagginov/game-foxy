#include "main_character.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

#define PI 3.1415926535897932384626433832795

void MainCharacter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_damage", "enemy_pos"), &MainCharacter::_damage);
	ClassDB::bind_method(D_METHOD("_dead"), &MainCharacter::_dead);
	ClassDB::bind_method(D_METHOD("_hit", "target_pos"), &MainCharacter::_hit);
}

MainCharacter::MainCharacter() {
	// Initialize any variables here.
	gm = nullptr;

	direction = VECTOR2_ZERO;

	state = States::idle;

	v_states.push_back(new State(0.0));		// idle
	v_states.push_back(new State(0.0));		// run
	v_states.push_back(new State(0.2));		// slide
	v_states.push_back(new State(0.2));		// attack
	v_states.push_back(new State(2.0));		// shot

	arrow = nullptr;

	arrow_line = nullptr;

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

	gm = GameManager::get_singleton();

	if (gm)
	{
		gm->give_mc_pointer(this);
		set_process_mode(PROCESS_MODE_INHERIT);
	}
	else
	{
		set_process_mode(PROCESS_MODE_DISABLED);
	}
	

	components = get_node<ComponentsContainer>("ComponentsContainer");
	components->bind(this);
	components->hitbox->turn_off();

	sword = get_node<Sprite2D>("Sword");

	arrow = get_node<Arrow>("Arrow");
	arrow_line = get_node<LineEdit>("ArrowLine");

	inventory = get_node<Inventory>("Inventory");
}

void MainCharacter::_process(double delta) 
{

}

void MainCharacter::_physics_process(double delta) 
{
	direction = gm->i->get_vector("ui_left", "ui_right", "ui_up", "ui_down").normalized();

	components->animation_controller->set_angle(direction);
	components->animation_controller->play_current_animation();

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

	case States::shot :
		f_shot(delta);
		break;
	}

	move(direction, delta);
}

void MainCharacter::_input(Ref<InputEvent> event)
{
    Ref<InputEventMouseButton> mouse_event = event;
    
    if (mouse_event.is_valid()) {
        if (mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT && mouse_event->is_pressed()) {
			if (gm->is_input_allowed() && state != States::slide)
			{
				change_state(States::idle);
				state = States::attack;
			}
        }
    }
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

	if (gm->i->is_action_just_pressed("ui_accept"))
	{
		change_state(States::slide);
	}

	if (gm->i->is_mouse_button_pressed(MouseButton::MOUSE_BUTTON_RIGHT) && !arrow->is_active())
	{
		change_state(States::shot);
	}
}

void MainCharacter::f_run(double delta)
{
	if (direction == VECTOR2_ZERO)
	{
		change_state(States::idle);
	}

	if (gm->i->is_action_just_pressed("ui_accept"))
	{
		change_state(States::slide);
		return;
	}

	if (gm->i->is_mouse_button_pressed(MouseButton::MOUSE_BUTTON_RIGHT) && !arrow->is_active())
	{
		change_state(States::shot);
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
		components->hitbox->set_rotation(angle);
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

void MainCharacter::f_shot(double delta)
{
	if (v_states[state]->is_start())
	{
		arrow_line->set_visible(true);
		components->animation_controller->set_state(static_cast<int>(States::idle));
	}

	if (!gm->i->is_mouse_button_pressed(MouseButton::MOUSE_BUTTON_RIGHT) && !v_states[state]->update(delta))
	{
		change_state(States::idle);
		arrow_line->set_visible(false);
		return;
	}

	if (v_states[state]->update(delta))
	{
		if (!gm->i->is_mouse_button_pressed(MouseButton::MOUSE_BUTTON_RIGHT))
		{
			Vector2 mouse_dir = gm->get_mouse_position() - arrow->get_global_position();
			mouse_dir = mouse_dir.normalized();

			double angle = -mouse_dir.angle_to(Vector2(0.0, -1.0));

			if (arrow)
			{
				arrow->set_rotation(angle);
				arrow->shot(mouse_dir);
			}
			
			change_state(States::idle);
			arrow_line->set_visible(false);
			return;
		}
	}

	int count_download = v_states[state]->get_current_time() / v_states[state]->get_max_time() * 7;

	if (count_download > 7)
	{
		if (arrow_line)
		{
			arrow_line->set_text("[#######]");
		}
	}
	else
	{
		if (arrow_line)
		{
			arrow_line->set_text(String("[" 
			+ String("#######").substr(0, count_download) 
			+ String("*******").substr(0, 7 - count_download) 
			+ String("]")));
		}
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
	UtilityFunctions::print("U are dead");
	get_tree()->change_scene_to_file("res://scenes/main_menu.tscn");
}

void MainCharacter::_hit(Vector2 target_pos)
{

}

void MainCharacter::change_state(States p_state)
{
	v_states[state]->reset();
	state = p_state;

	components->animation_controller->set_state(static_cast<int>(state));
}


Dictionary MainCharacter::save()
{
	Dictionary info;

	Vector2 pos = get_global_position();
	info["x_pos"] = pos.x;
	info["y_pos"] = pos.y;

	info["hp"] = components->health->get_hp();

	info["inventory"] = inventory->save();

	return info;
}

void MainCharacter::load(const Dictionary& info)
{
	components->health->set_hp(info["hp"]);
	set_global_position(Vector2(info["x_pos"], info["y_pos"]));
	if (info.has("inventory"))
	{
		if (info["inventory"].get_type() == Variant::DICTIONARY)
		{
			Dictionary inventory_info = info["inventory"];
			inventory->load(inventory_info);
		}
	}
}