#include "custom_CharacterBody2D.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void CustomCharacterBody2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &CustomCharacterBody2D::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &CustomCharacterBody2D::set_speed);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}


CustomCharacterBody2D::CustomCharacterBody2D() {
	speed = 400.0;
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
	set_velocity(input_direction * speed);

	move_and_slide();
}


void CustomCharacterBody2D::set_speed(const double p_speed) {
	speed = p_speed;
}

double CustomCharacterBody2D::get_speed() const {
	return speed;
}