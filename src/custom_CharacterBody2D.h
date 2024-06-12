#ifndef CUSTOM_CHARACTER_BODY2D_H
#define CUSTOM_CHARACTER_BODY2D_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/templates/hash_set.hpp>

namespace godot {

class CustomCharacterBody2D : public CharacterBody2D {
	GDCLASS(CustomCharacterBody2D, CharacterBody2D)

private:
	Input* i;

	// Vars for dodge
	double dodge_time;
	bool in_dodge;

	// Vars for sword attack
	HashSet<Node2D*> object_set;

	Vector2 direction;
	Area2D* attack_area;
    CollisionShape2D* attack_shape;
	Sprite2D* sword;
	bool anim_sword_attack;
	double time_sword_attack;
	RayCast2D *ray_cast;

	// Label for print debug info
	Label* label;

	// Vars for animated main character
	AnimatedSprite2D* animatedSprite;
	Vector<String> animmationVector;
	int animationVariant;
	bool animHelper;

public:
	double hp, max_hp; // default 4 hp
	
	double speed;   // meters in second; default 2 m/s
	double pixels_in_meter; // count pixels in one meter; default 32 px/m

	double length_dodge_line; // default 2 meters
	double dodge_execution_time; // default 0.1 seconds

protected:
	static void _bind_methods();

public:
	CustomCharacterBody2D();
	~CustomCharacterBody2D();

    void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void _on_detection_area_entered(Node2D *area);
    void _on_detection_area_exited(Node2D *area);

	bool dodge_method(double delta);
	void sword_attack();
	
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