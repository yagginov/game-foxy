#include "baseEnemy.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void BaseEnemy::_bind_methods() {
    ClassDB::bind_method(D_METHOD("take_damage", "amount"), &BaseEnemy::take_damage);

    ClassDB::bind_method(D_METHOD("get_speed"), &BaseEnemy::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &BaseEnemy::set_speed);
	ClassDB::add_property("BaseEnemy", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

	ClassDB::bind_method(D_METHOD("get_pixels_in_meter"), &BaseEnemy::get_pixels_in_meter);
	ClassDB::bind_method(D_METHOD("set_pixels_in_meter", "p_pixels_in_meter"), &BaseEnemy::set_pixels_in_meter);
	ClassDB::add_property("BaseEnemy", PropertyInfo(Variant::FLOAT, "pixels_in_meter"), "set_pixels_in_meter", "get_pixels_in_meter");

    ClassDB::bind_method(D_METHOD("get_hp"), &BaseEnemy::get_hp);
	ClassDB::bind_method(D_METHOD("set_hp", "p_hp"), &BaseEnemy::set_hp);
	ClassDB::add_property("BaseEnemy", PropertyInfo(Variant::FLOAT, "hp"), "set_hp", "get_hp");

	ClassDB::bind_method(D_METHOD("get_attack"), &BaseEnemy::get_attack);
	ClassDB::bind_method(D_METHOD("set_attack", "p_attack"), &BaseEnemy::set_attack);
	ClassDB::add_property("BaseEnemy", PropertyInfo(Variant::FLOAT, "attack"), "set_attack", "get_attack");

}

BaseEnemy::BaseEnemy() {
    hp = 0.0;
	pixels_in_meter = 32.0;
	attack = 0.0;
	speed = 0.0;
}

BaseEnemy::~BaseEnemy() {
}

void BaseEnemy::take_damage(int amount) {
    hp -= amount;
    if (hp <= 0) {
        hp = 0;
    }
}

void BaseEnemy::set_speed(const double p_speed) {
	speed = p_speed;
}

double BaseEnemy::get_speed() const {
	return speed;
}

void BaseEnemy::set_pixels_in_meter(const double p_pixels_in_meter) {
	pixels_in_meter = p_pixels_in_meter;
}

double BaseEnemy::get_pixels_in_meter() const {
	return pixels_in_meter;
}

void BaseEnemy::set_hp(const double p_hp) {
	if (p_hp < 0.0) { hp = 0.0; return; }

	hp = p_hp;
}

double BaseEnemy::get_hp() const {
	return hp;
}

void BaseEnemy::set_attack(const double p_attack) {
	attack = p_attack;
}

double BaseEnemy::get_attack() const {
	return attack;
}