#include "custom_CharacterBody2D.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_shape_query_parameters2d.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;


void CustomCharacterBody2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("sword_attack"), &CustomCharacterBody2D::sword_attack);
	
	ClassDB::bind_method(D_METHOD("get_speed"), &CustomCharacterBody2D::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &CustomCharacterBody2D::set_speed);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

	ClassDB::bind_method(D_METHOD("get_pixels_in_meter"), &CustomCharacterBody2D::get_pixels_in_meter);
	ClassDB::bind_method(D_METHOD("set_pixels_in_meter", "p_pixels_in_meter"), &CustomCharacterBody2D::set_pixels_in_meter);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "pixels_in_meter"), "set_pixels_in_meter", "get_pixels_in_meter");

	ClassDB::bind_method(D_METHOD("get_dodge_execution_time"), &CustomCharacterBody2D::get_dodge_execution_time);
	ClassDB::bind_method(D_METHOD("set_dodge_execution_time", "p_dodge_execution_time"), &CustomCharacterBody2D::set_dodge_execution_time);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "dodge_execution_time"), "set_dodge_execution_time", "get_dodge_execution_time");

	ClassDB::bind_method(D_METHOD("get_length_dodge_line"), &CustomCharacterBody2D::get_length_dodge_line);
	ClassDB::bind_method(D_METHOD("set_length_dodge_line", "p_length_dodge_line"), &CustomCharacterBody2D::set_length_dodge_line);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "length_dodge_line"), "set_length_dodge_line", "get_length_dodge_line");

	ClassDB::bind_method(D_METHOD("get_hp"), &CustomCharacterBody2D::get_hp);
	ClassDB::bind_method(D_METHOD("set_hp", "p_hp"), &CustomCharacterBody2D::set_hp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "hp"), "set_hp", "get_hp");

	ClassDB::bind_method(D_METHOD("get_max_hp"), &CustomCharacterBody2D::get_max_hp);
	ClassDB::bind_method(D_METHOD("set_max_hp", "p_max_hp"), &CustomCharacterBody2D::set_max_hp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "max_hp"), "set_max_hp", "get_max_hp");
}


CustomCharacterBody2D::CustomCharacterBody2D() {
	// Initialize any variables here.
	speed = 2.0; // 2 m/s
	pixels_in_meter = 32.0; // 32 px/m
	i = Input::get_singleton();

	dodge_helper = Vector2(0.0, 0.0);
	dodge_time = 0.0f;
	in_dodge = false;

	length_dodge_line = 2;
	dodge_execution_time = 0.1;

	max_hp = 4.0; hp = 4.0;
	attack_radius = 3.0;

	direction = Vector2(1.0, 0.0);
	attack_area = nullptr;
    attack_shape = nullptr;

}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_ready() {
    // Get the attack area and shape
    attack_area = get_node<Area2D>("AttackArea");
    if (attack_area) {
        attack_shape = attack_area->get_node<CollisionShape2D>("CollisionShape2D");
    }
}

void CustomCharacterBody2D::_process(double delta) {

}

void CustomCharacterBody2D::_physics_process(double delta) {
	// Check sword attack
	if (i->is_action_just_pressed("attack"))
	{
		sword_attack();
	}

	// Check dodge
	if (dodge_method(delta)) { return; }

	// Movement logic--------------
	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
	if (input_direction.x != 0.0 || input_direction.y != 0.0)
	{
		direction = input_direction.normalized();
	}
	set_velocity(input_direction * speed * pixels_in_meter);
	move_and_slide();
}


bool CustomCharacterBody2D::dodge_method(double delta)
{
	// Dodge logic--------------
	if (i->is_action_just_pressed("dodge"))
	{
		dodge_helper = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
		if (dodge_helper.x == 0 && dodge_helper.y == 0)
		{
			return false;
		}
		in_dodge = true;
	}
	else if (!in_dodge)
	{
		return false;
	}

	set_velocity(dodge_helper * (length_dodge_line / dodge_execution_time) * pixels_in_meter);
	move_and_slide();
	dodge_time += delta;
	
	if (dodge_time > dodge_execution_time)
	{
		in_dodge = false;
		dodge_time = 0.0;
	}
	return true;
}

void CustomCharacterBody2D::sword_attack() {
    if (!attack_area || !attack_shape) {
        return;
    }

    // Get the current space state to perform collision checks
    PhysicsDirectSpaceState2D* space_state = get_world_2d()->get_direct_space_state();
    
    // Set up the shape query parameters
    PhysicsShapeQueryParameters2D* params = new PhysicsShapeQueryParameters2D;
    params->set_shape(attack_shape->get_shape());
    params->set_transform(attack_area->get_global_transform());

    // Perform the shape query
    TypedArray<Dictionary> results = space_state->intersect_shape(params, 32);

	String collider_name = String("");
		

    for (int i = 0; i < results.size(); ++i) {
        Dictionary result = results[i];
        Node2D *collider = Object::cast_to<Node2D>(result["collider"]);

        if (!collider) {
            continue;
        }
		
        // Check if the collider is in the forward half circle
        Vector2 relative_position = collider->get_global_position() - get_global_position();
		double angle = relative_position.angle_to(direction);
		if (angle < 1.5708 || angle > 4.71239) {
            // Inflict damage on the collider
            if (collider->has_method("take_damage")) {
                collider->call("take_damage", 1);
            }
    	}
	}
}

void CustomCharacterBody2D::set_speed(const double p_speed) {
	speed = p_speed;
}

double CustomCharacterBody2D::get_speed() const {
	return speed;
}

void CustomCharacterBody2D::set_pixels_in_meter(const double p_pixels_in_meter) {
	pixels_in_meter = p_pixels_in_meter;
}

double CustomCharacterBody2D::get_pixels_in_meter() const {
	return pixels_in_meter;
}

void CustomCharacterBody2D::set_dodge_execution_time(const double p_dodge_execution_time) {
	dodge_execution_time = p_dodge_execution_time;
}

double CustomCharacterBody2D::get_dodge_execution_time() const {
	return dodge_execution_time;
}

void CustomCharacterBody2D::set_length_dodge_line(const double p_length_dodge_line) {
	length_dodge_line = p_length_dodge_line;
}

double CustomCharacterBody2D::get_length_dodge_line() const {
	return length_dodge_line;
}

void CustomCharacterBody2D::set_hp(const double p_hp) {
	if (p_hp > max_hp) { hp = max_hp; return; }
	if (p_hp < 0.0) { hp = 0.0; return; }

	hp = p_hp;
}

double CustomCharacterBody2D::get_hp() const {
	return hp;
}

void CustomCharacterBody2D::set_max_hp(const double p_max_hp) {
	if (p_max_hp < 0.0) { max_hp = 0.0; return; }

	max_hp = p_max_hp;
}

double CustomCharacterBody2D::get_max_hp() const {
	return max_hp;
}