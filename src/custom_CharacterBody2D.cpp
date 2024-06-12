#include "custom_CharacterBody2D.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_shape_query_parameters2d.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>

using namespace godot;


void CustomCharacterBody2D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_detection_area_entered", "area"), &CustomCharacterBody2D::_on_detection_area_entered);
    ClassDB::bind_method(D_METHOD("_on_detection_area_exited", "area"), &CustomCharacterBody2D::_on_detection_area_exited);
	
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
	max_hp = 4.0; hp = 4.0;
	
	speed = 2.0;
	pixels_in_meter = 32.0;
	
	i = Input::get_singleton();

	dodge_time = 0.0;
	in_dodge = false;
	length_dodge_line = 2;
	dodge_execution_time = 0.1;

	direction = Vector2(1.0, 0.0);
	attack_area = nullptr;
    attack_shape = nullptr;
	label = nullptr;
	anim_sword_attack = false;
	time_sword_attack = 0.0;
	ray_cast = nullptr;

	animationVariant = 0;
	animmationVector = {String("idleRight"), String("idleLeft"), String("idleUp"), String("idleDown"), 
	String("dodgeRight"), String("dodgeLeft"), String("dodgeUp"), String("dodgeDown")};
	animHelper = true;

}

CustomCharacterBody2D::~CustomCharacterBody2D() {
	// Add your cleanup here.
}

void CustomCharacterBody2D::_ready() {
	add_to_group("Player");
	label = get_node<Label>("Label");
	sword = get_node<Sprite2D>("Sword");
	animatedSprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	ray_cast = get_node<RayCast2D>("RayCast2D");
	if (ray_cast)
    {
        ray_cast->set_collide_with_bodies(true);
        ray_cast->set_collide_with_areas(true);
    }

    // Get the attack area and shape
    attack_area = get_node<Area2D>("HitBox");
    if (attack_area) {
        attack_shape = attack_area->get_node<CollisionShape2D>("CollisionShape2D");
    }

	attack_area->connect("area_entered", Callable(this, "_on_detection_area_entered"));
    attack_area->connect("area_exited", Callable(this, "_on_detection_area_exited"));
}

void CustomCharacterBody2D::_process(double delta) {

}

void CustomCharacterBody2D::_physics_process(double delta) {
	// Check sword attack
	if (i->is_action_just_pressed("attack"))
	{
		sword_attack();
	}

	// Draw animation sword attack
	if (anim_sword_attack)
	{
		time_sword_attack += delta;
		sword->rotate(3.14159 * (delta / 0.2));

		if (time_sword_attack > 0.2)
		{
			anim_sword_attack = false;
			sword->set_visible(false);
			time_sword_attack = 0.0;
		}
	}

	// Check dodge
	if (dodge_method(delta)) { return; }

	// Movement logic--------------
	Vector2 input_direction = i->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
	
	// Animation main character logic
	if (input_direction.y < 0.0) { animatedSprite->play("runUp"); animationVariant = 2; animHelper = true; }
	else if (input_direction.y > 0.0) { animatedSprite->play("runDown"); animationVariant = 3; animHelper = true; }
	else if (input_direction.x > 0.0) { animatedSprite->play("runRight"); animationVariant = 0; animHelper = true; }
	else if (input_direction.x < 0.0) { animatedSprite->play("runLeft"); animationVariant = 1; animHelper = true; }
	else if (animHelper){ animatedSprite->play(animmationVector[animationVariant]); animHelper = false; }
	
	if (input_direction.x != 0.0 || input_direction.y != 0.0) { direction = input_direction.normalized(); }

	// Base movement
	set_velocity(input_direction * speed * pixels_in_meter);
	move_and_slide();
}


bool CustomCharacterBody2D::dodge_method(double delta)
{
	// Dodge logic--------------
	if (!in_dodge && i->is_action_just_pressed("dodge"))
	{
		in_dodge = true;
		animatedSprite->play(animmationVector[animationVariant + 4]);
		animHelper = true;
	}
	else if (!in_dodge)
	{
		return false;
	}

	set_velocity(direction * (length_dodge_line / dodge_execution_time) * pixels_in_meter);
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
	if (anim_sword_attack) { return; }

	sword->set_rotation(Vector2(0.0, 1.0).angle_to(direction) + 1.5708);
	sword->set_visible(true);
	anim_sword_attack = true;
	time_sword_attack = 0.0;

    if (!attack_area || !attack_shape) {
        return;
    }

    for (auto& it : object_set) {
        // Check if the collider is in the forward half circle
        Vector2 relative_position = it->get_global_position() - attack_shape->get_global_position();

		ray_cast->set_target_position(relative_position);
		ray_cast->force_raycast_update();
		if (ray_cast->is_colliding())
		{
			Node *coll = Object::cast_to<Node2D>(ray_cast->get_collider());  
            coll = Object::cast_to<Node2D>(coll->get_parent());
			if (!coll->is_in_group("Enemy") && !coll->is_in_group("HitItems"))
			{
				continue;
			}
		}

		double angle = relative_position.angle_to(direction);
		if (angle < 0.0) { angle = -angle; }

		if (angle < 1.7 || angle > 4.5) {
			it->call("take_damage", 1);
    	}
	}
}


void CustomCharacterBody2D::_on_detection_area_entered(Node2D *area) {
    area = Object::cast_to<Node2D>(area->get_parent());

    if (area->is_in_group("Enemy") || area->is_in_group("HitItems")) {
		object_set.insert(area);
    }
}

void CustomCharacterBody2D::_on_detection_area_exited(Node2D *area) {
    area = Object::cast_to<Node2D>(area->get_parent());
    if (object_set.has(area)) {
		object_set.erase(area);
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