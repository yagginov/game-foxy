#include "animation_controller.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AnimationController::_bind_methods() 
{
	
}


AnimationController::AnimationController()
{
	// Initialize any variables here.	
    current_angle = Angle::right;
    current_state = States::idle;

    vs_states.push_back("idle_");
    vs_states.push_back("run_");
    vs_states.push_back("slide_");

    vs_angles.push_back("up");
    vs_angles.push_back("left");
    vs_angles.push_back("down");
    vs_angles.push_back("right");

    angle_vector = Vector2(1, 0);
}

AnimationController::~AnimationController() 
{

}

void AnimationController::_ready() 
{

}


bool AnimationController::play_current_animation(float custom_speed)
{
    String current_animation = vs_states[current_state] + vs_angles[current_angle];
    play(current_animation, custom_speed);

    return !is_playing();
}

void AnimationController::set_state(const int state)
{
    switch (state)
    {
    case 0:
        current_state = States::idle;
        return;
    case 1:
        current_state = States::run;
        return;
    case 2:
        current_state = States::slide;
        return;
    }
}

void AnimationController::set_angle(const Vector2 direction)
{
    if (direction == VECTOR2_ZERO || direction == angle_vector) { return; }

    angle_vector = direction;

    if (angle_vector.x > 0) { current_angle = Angle::right; }
    else if (angle_vector.x < 0) { current_angle = Angle::left; }
    else if (angle_vector.y > 0) { current_angle = Angle::down; }
    else { current_angle = Angle::up; }
}

Vector2 AnimationController::get_angle_vector() const
{
    return angle_vector;
}