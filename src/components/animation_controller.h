#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot {

class AnimationController : public AnimatedSprite2D {
	GDCLASS(AnimationController, AnimatedSprite2D)

enum States
{
	idle = 0,
	run = 1,
	slide = 2
};

enum Angle
{
    up = 0,
    left = 1,
    down = 2,
    right = 3
};

const Vector2 VECTOR2_ZERO = Vector2(0.0, 0.0);

protected:
	static void _bind_methods();

private:
    Angle current_angle;
    States current_state;

    Vector<String> vs_states;
    Vector<String> vs_angles;

    Vector2 angle_vector;

public:
	AnimationController();
	~AnimationController();

    void _ready() override;

    bool play_current_animation(float custom_speed = 1.0);

    void set_state(const int state);
    void set_angle(const Vector2 direction);

    Vector2 get_angle_vector() const;

};

}	// namespace godot

#endif	// ANIMATION_CONTROLLER_H