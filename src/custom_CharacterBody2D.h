#ifndef CUSTOM_CHARACTER_BODY2D_H_H
#define CUSTOM_CHARACTER_BODY2D_H_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot {

class CustomCharacterBody2D : public CharacterBody2D {
	GDCLASS(CustomCharacterBody2D, CharacterBody2D)

private:
	Input* i;
	Vector2 dodge_helper;
	double dodge_time;
	bool in_dodge;

public:
	double speed;   // meters in second; default 2 m/s
	double pixels_in_meter; // count pixels in one meter; default 32 px/m
	double length_dodge_line; // default 2 meters
	double dodge_execution_time; // default 0.5 seconds
	double hp, max_hp; // default 4 hp

protected:
	static void _bind_methods();

public:
	CustomCharacterBody2D();
	~CustomCharacterBody2D();

	void _process(double delta) override;
	void _physics_process(double delta) override;

	bool dodge_method(double delta);
	
	void set_speed(const double p_speed);
	double get_speed() const;

	void set_pixels_in_meter(const double p_pixels_in_meter);
	double get_pixels_in_meter() const;

	void set_length_dodge_line(const double p_length_dodge_line);
	double get_length_dodge_line() const;

	void set_dodge_execution_time(const double p_dodge_execution_time);
	double get_dodge_execution_time() const;

	void set_hp(const double p_hp);
	double get_hp() const;

	void set_max_hp(const double p_max_hp);
	double get_max_hp() const;
};

}

#endif