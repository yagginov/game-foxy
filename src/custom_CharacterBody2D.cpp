#include "custom_CharacterBody2D.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void CustomCharacterBody2D::_bind_methods() {
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
}


CustomCharacterBody2D::CustomCharacterBody2D() {
	// Initialize any variables here.
	speed = 2.0; // 2 m/s
	pixels_in_meter = 32.0; // 32 pixels/m
	i = Input::get_singleton();

	dodge_helper = Vector2(0.0, 0.0);
	dodge_time = 0.0f;
	in_dodge = false;

	length_dodge_line = 2;
	dodge_execution_time = 0.5;

}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_process(double delta) {

}

void CustomCharacterBody2D::_physics_process(double delta) {
	
	// Check dodge
	if (dodge_method(delta)) { return; }

	// Movement logic--------------
	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
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