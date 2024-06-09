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

	ClassDB::bind_method(D_METHOD("get_rs_hp"), &CustomCharacterBody2D::get_rs_hp);
	ClassDB::bind_method(D_METHOD("set_rs_hp", "p_rs_hp"), &CustomCharacterBody2D::set_rs_hp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "rs_hp"), "set_rs_hp", "get_rs_hp");

	ClassDB::bind_method(D_METHOD("get_rs_stamina"), &CustomCharacterBody2D::get_rs_stamina);
	ClassDB::bind_method(D_METHOD("set_rs_stamina", "p_rs_stamina"), &CustomCharacterBody2D::set_rs_stamina);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "rs_stamina"), "set_rs_stamina", "get_rs_stamina");

	ClassDB::bind_method(D_METHOD("get_rs_mp"), &CustomCharacterBody2D::get_rs_mp);
	ClassDB::bind_method(D_METHOD("set_rs_mp", "p_rs_mp"), &CustomCharacterBody2D::set_rs_mp);
	ClassDB::add_property("CustomCharacterBody2D", PropertyInfo(Variant::FLOAT, "rs_mp"), "set_rs_mp", "get_rs_mp");

}


CustomCharacterBody2D::CustomCharacterBody2D() {
	// Initialize any variables here.
	speed = 400.0;
	i = Input::get_singleton();
	
	hp = 100.0; stamina = 100.0; mp = 100.0;
	max_hp = 100.0; max_stamina = 100.0; max_mp = 100.0;
	rs_hp = 1.0; rs_stamina = 1.0; rs_mp = 1.0;

	sprint_helper = false;
}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_process(double delta) {
	
}

void CustomCharacterBody2D::_physics_process(double delta) {	
	if (!Engine::get_singleton()->is_editor_hint() && i->is_action_just_pressed("sprint")){
		if (sprint_helper) { speed /= 2.0; sprint_helper = false; }
		else { speed *= 2.0; sprint_helper = true; }
	}

	if (sprint_helper){
		stamina -= delta * 2.0;
		if (stamina < 0.0) { stamina = 0.0; sprint_helper = false; }
	}
	else {
		stamina_recovery(delta);
	}

	hp_recovery(delta);
	mp_recovery(delta);

	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
	set_velocity(input_direction * speed);

	move_and_slide();
}

inline void CustomCharacterBody2D::hp_recovery(double delta) {
	if (hp < max_hp)
	{
		hp += rs_hp * delta;
		if (hp > max_hp) { hp = max_hp; }
	}
}

inline void CustomCharacterBody2D::stamina_recovery(double delta) {
	if (stamina < max_stamina)
	{
		stamina += rs_stamina * delta;
		if (stamina > max_stamina) { stamina = max_stamina; }
	}
}

inline void CustomCharacterBody2D::mp_recovery(double delta) {
	if (mp < max_mp)
	{
		mp += rs_mp * delta;
		if (mp > max_mp) { mp = max_mp; }
	}
}


void CustomCharacterBody2D::set_speed(const double p_speed) {
	speed = p_speed;
}

double CustomCharacterBody2D::get_speed() const {
	return speed;
}


void CustomCharacterBody2D::set_hp(const double p_hp) {
	if (p_hp > max_hp)
	{
		return;
	}
	hp = p_hp;
}

double CustomCharacterBody2D::get_hp() const {
	return hp;
}

void CustomCharacterBody2D::set_stamina(const double p_stamina) {
	if (p_stamina > max_stamina)
	{
		return;
	}
	stamina = p_stamina;
}

double CustomCharacterBody2D::get_stamina() const {
	return stamina;
}

void CustomCharacterBody2D::set_mp(const double p_mp) {
	if (p_mp > max_mp)
	{
		return;
	}
	mp = p_mp;
}

double CustomCharacterBody2D::get_mp() const {
	return mp;
}



void CustomCharacterBody2D::set_max_hp(const double p_max_hp) {
	max_hp = p_max_hp;
	hp = max_hp;
}

double CustomCharacterBody2D::get_max_hp() const {
	return max_hp;
}

void CustomCharacterBody2D::set_max_stamina(const double p_max_stamina) {
	max_stamina = p_max_stamina;
	stamina = max_stamina;
}

double CustomCharacterBody2D::get_max_stamina() const {
	return max_stamina;
}

void CustomCharacterBody2D::set_max_mp(const double p_max_mp) {
	max_mp = p_max_mp;
	mp = max_mp;
}

double CustomCharacterBody2D::get_max_mp() const {
	return max_mp;
}


void CustomCharacterBody2D::set_rs_hp(const double p_rs_hp) {
	rs_hp = p_rs_hp;
}

double CustomCharacterBody2D::get_rs_hp() const {
	return rs_hp;
}

void CustomCharacterBody2D::set_rs_stamina(const double p_rs_stamina) {
	rs_stamina = p_rs_stamina;
}

double CustomCharacterBody2D::get_rs_stamina() const {
	return rs_stamina;
}

void CustomCharacterBody2D::set_rs_mp(const double p_rs_mp) {
	rs_mp = p_rs_mp;
}

double CustomCharacterBody2D::get_rs_mp() const {
	return rs_mp;
}