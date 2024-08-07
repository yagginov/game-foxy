#include "arrow.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Arrow::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("get_max_count_of_targets"), &Arrow::get_max_count_of_targets);
	ClassDB::bind_method(D_METHOD("set_max_count_of_targets", "p_max_count_of_targets"), &Arrow::set_max_count_of_targets);
	ClassDB::add_property("Arrow", PropertyInfo(Variant::INT, "max_count_of_targets"), "set_max_count_of_targets", "get_max_count_of_targets");

    ClassDB::bind_method(D_METHOD("get_max_distance"), &Arrow::get_max_distance);
	ClassDB::bind_method(D_METHOD("set_max_distance", "p_max_distance"), &Arrow::set_max_distance);
	ClassDB::add_property("Arrow", PropertyInfo(Variant::FLOAT, "max_distance"), "set_max_distance", "get_max_distance");

    ClassDB::bind_method(D_METHOD("get_sprite_path"), &Arrow::get_sprite_path);
	ClassDB::bind_method(D_METHOD("set_sprite_path", "p_sprite_path"), &Arrow::set_sprite_path);
	ClassDB::add_property("Arrow", PropertyInfo(Variant::NODE_PATH, "sprite_path"), "set_sprite_path", "get_sprite_path");

    ClassDB::bind_method(D_METHOD("turn_on"), &Arrow::turn_on);
    ClassDB::bind_method(D_METHOD("turn_off"), &Arrow::turn_off);
}

Arrow::Arrow() 
{
	// Initialize any variables here.	
	max_count_of_targets = 1;
    count_of_targets = 0;
    sprite = nullptr;

    distance = 0;
    max_distance = 32 * 8;
    prev_position = Vector2(0.0, 0.0);
    direction = Vector2(0.0, 0.0);

    velocity = Vector2(0.0, 0.0);
    speed = 400;
    acceleration = 1500;

    v_states.push_back(new State(0.0));
    v_states.push_back(new State(0.0));

    state = States::calm;

}

Arrow::~Arrow() 
{
	// Add your cleanup here.

}

void Arrow::_ready() 
{
	add_to_group("Arrow");

    Hitbox::_ready();

    if (has_node(sprite_path)) {
        sprite = get_node<Sprite2D>(sprite_path); 
        UtilityFunctions::print("sprite received");
    }

    UtilityFunctions::print("arrow _ready() success");
}

void Arrow::_physics_process(double delta) 
{
	switch(state)
	{
	case States::fly :
		f_fly(delta);
		break;
    default:
        if (v_states[state]->is_start())
        {
            turn_off();
        } 
        break;
	}
}

void Arrow::f_fly(double delta)
{
    if (v_states[state]->is_start())
    {
        this->turn_on();
        prev_position = get_global_position();
    }
    
    distance += (get_global_position() - prev_position).length(); 
    prev_position = get_global_position();
    
    velocity = velocity.move_toward(direction * speed, acceleration * delta);
    set_global_position(get_global_position() + velocity * delta);

    if (distance > max_distance)
    {
        reset();
    }
}

void Arrow::hit(Vector2 target_pos)
{
    Hitbox::hit(target_pos);
    if (++count_of_targets >= max_count_of_targets)
    {
        reset();
    }
}

void Arrow::turn_on()
{

    Hitbox::turn_on();

    if (sprite)
    {
        sprite->set_visible(true);
    }
}

void Arrow::turn_off()
{
    Hitbox::turn_off();
}

void Arrow::reset()
{
    v_states[state]->reset();
    state = States::calm;
    distance = 0.0;
    count_of_targets = 0;
    velocity = Vector2(0.0, 0.0);
    set_position(Vector2(0.0, -13.0));

    if (sprite)
    {
        sprite->set_visible(false);
    }
}

void Arrow::shot(const Vector2 p_direction)
{
    reset();
    state = States::fly;
    direction = p_direction;
}

bool Arrow::is_active() const
{
    if (sprite)
    {
        return sprite->is_visible();
    }
    return true;
}


void Arrow::set_sprite_path(const NodePath& p_sprite_path)
{
    sprite_path = p_sprite_path;
}
NodePath Arrow::get_sprite_path() const
{
    return sprite_path;
}

void Arrow::set_max_count_of_targets(const int p_max_count_of_targets)
{
    max_count_of_targets = p_max_count_of_targets;
}
int Arrow::get_max_count_of_targets() const
{
    return max_count_of_targets;
}

void Arrow::set_max_distance(const double p_max_distance)
{
    max_distance = p_max_distance;
}
double Arrow::get_max_distance() const
{
    return max_distance;
}