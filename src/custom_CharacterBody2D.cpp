#include "custom_CharacterBody2D.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void CustomCharacterBody2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &CustomCharacterBody2D::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &CustomCharacterBody2D::set_speed);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

	ClassDB::bind_method(D_METHOD("get_hp"), &CustomCharacterBody2D::get_hp);
	ClassDB::bind_method(D_METHOD("set_hp", "p_hp"), &CustomCharacterBody2D::set_hp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "hp"), "set_hp", "get_hp");

	ClassDB::bind_method(D_METHOD("get_stamina"), &CustomCharacterBody2D::get_stamina);
	ClassDB::bind_method(D_METHOD("set_stamina", "p_stamina"), &CustomCharacterBody2D::set_stamina);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "stamina"), "set_stamina", "get_stamina");

	ClassDB::bind_method(D_METHOD("get_mp"), &CustomCharacterBody2D::get_mp);
	ClassDB::bind_method(D_METHOD("set_mp", "p_mp"), &CustomCharacterBody2D::set_mp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "mp"), "set_mp", "get_mp");

	ClassDB::bind_method(D_METHOD("get_max_hp"), &CustomCharacterBody2D::get_max_hp);
	ClassDB::bind_method(D_METHOD("set_max_hp", "p_max_hp"), &CustomCharacterBody2D::set_max_hp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "max_hp"), "set_max_hp", "get_max_hp");

	ClassDB::bind_method(D_METHOD("get_max_stamina"), &CustomCharacterBody2D::get_max_stamina);
	ClassDB::bind_method(D_METHOD("set_max_stamina", "p_max_stamina"), &CustomCharacterBody2D::set_max_stamina);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "max_stamina"), "set_max_stamina", "get_max_stamina");

	ClassDB::bind_method(D_METHOD("get_max_mp"), &CustomCharacterBody2D::get_max_mp);
	ClassDB::bind_method(D_METHOD("set_max_mp", "p_max_mp"), &CustomCharacterBody2D::set_max_mp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "max_mp"), "set_max_mp", "get_max_mp");

}


CustomCharacterBody2D::CustomCharacterBody2D() {
	// Initialize any variables here.
	speed = 400.0;
	i = Input::get_singleton();
	
	hp = 100;
	stamina = 100;
	mp = 100;

	max_hp = 100;
	max_stamina = 100;
	max_mp = 100;

	hp_helper = 0.0f;
}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_process(double delta) {

}

void CustomCharacterBody2D::_physics_process(double delta) {	
	hp_recovery();
	stamina_recovery();
	mp_recovery();

	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
	set_velocity(input_direction * speed);

	move_and_slide();
}

inline void CustomCharacterBody2D::hp_recovery() {
	if (hp < max_hp)
	{
		hp_helper += 0.017;
		if (hp_helper > 1.0f)
		{
			++hp;
			hp_helper = 0.0f;
		}
	}
}

inline void CustomCharacterBody2D::stamina_recovery() {
	if (stamina < max_stamina)
	{
		stamina_helper += 0.017;
		if (stamina_helper > 1.0f)
		{
			++stamina;
			stamina_helper = 0.0f;
		}
	}
}

inline void CustomCharacterBody2D::mp_recovery() {
	if (mp < max_mp)
	{
		mp_helper += 0.017;
		if (mp_helper > 1.0f)
		{
			++mp;
			mp_helper = 0.0f;
		}
	}
}


void CustomCharacterBody2D::set_speed(const double p_speed) {
	speed = p_speed;
}

double CustomCharacterBody2D::get_speed() const {
	return speed;
}


void CustomCharacterBody2D::set_hp(const int p_hp) {
	hp = p_hp;
}

int CustomCharacterBody2D::get_hp() const {
	return hp;
}

void CustomCharacterBody2D::set_stamina(const int p_stamina) {
	stamina = p_stamina;
}

int CustomCharacterBody2D::get_stamina() const {
	return stamina;
}

void CustomCharacterBody2D::set_mp(const int p_mp) {
	mp = p_mp;
}

int CustomCharacterBody2D::get_mp() const {
	return mp;
}



void CustomCharacterBody2D::set_max_hp(const int p_max_hp) {
	max_hp = p_max_hp;
}

int CustomCharacterBody2D::get_max_hp() const {
	return max_hp;
}

void CustomCharacterBody2D::set_max_stamina(const int p_max_stamina) {
	max_stamina = p_max_stamina;
}

int CustomCharacterBody2D::get_max_stamina() const {
	return max_stamina;
}

void CustomCharacterBody2D::set_max_mp(const int p_max_mp) {
	max_mp = p_max_mp;
}

int CustomCharacterBody2D::get_max_mp() const {
	return max_mp;
}