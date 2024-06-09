#ifndef CUSTOM_CHARACTER_BODY2D_H_H
#define CUSTOM_CHARACTER_BODY2D_H_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot {

class CustomCharacterBody2D : public CharacterBody2D {
	GDCLASS(CustomCharacterBody2D, CharacterBody2D)

private:
	Input* i;

public:
	double speed;

protected:
	static void _bind_methods();

public:
	CustomCharacterBody2D();
	~CustomCharacterBody2D();

	void _process(double delta) override;
	void _physics_process(double delta) override;
	
	void set_speed(const double p_speed);
	double get_speed() const;
};

}

#endif