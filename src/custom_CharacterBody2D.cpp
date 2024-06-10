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
}


CustomCharacterBody2D::CustomCharacterBody2D() {
	speed = 3.0; // 3 m/s
	pixels_in_meter = 32.0; // 32 pixels/m
	i = Input::get_singleton();
	// Initialize any variables here.
}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_process(double delta) {

}

void CustomCharacterBody2D::_physics_process(double delta) {
	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
	set_velocity(input_direction * speed * pixels_in_meter);

	move_and_slide();
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