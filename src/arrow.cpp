#include "arrow.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Arrow::_bind_methods() 
{
	
}

Arrow::Arrow() 
{
	// Initialize any variables here.	
	max_count_of_targets = 1;
    count_of_targets = 0;
    sprite_path = nullptr;
    sprite = nullptr;

    distance = 0;
    max_distance = 32 * 8;
    prev_position = Vector(0.0, 0.0);
    direction = Vector2(0.0, 0.0);

    v_states.push_back(new State(0.0));
    v_states.push_back(new States(0.0));

}

Arrow::~Arrow() 
{
	// Add your cleanup here.

}

void Arrow::_ready() 
{
	add_to_group("Arrow");


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
    if (v_states[state].is_start())
    {
        turn_on();
        prev_position = get_global_position();
    }
    
    distance += (get_global_position() - prev_position).length(); 
    
    if (distance > max_distance)
    {
        reset();
    }
}

void Arrow::hit(Vector2 target_pos)
{
    Hitbox::hit(target_pos);
    if (++count_of_targets > max_count_of_targets)
    {
        reset();
    }
}

void Arrow::turn_on()
{
    Hitbox::turn_on();
    if (sprite)
    {
        sprite.set_visible(true);
    }
}

void Arrow::turn_off()
{
    Hitbox::turn_off();
    if (sprite)
    {
        sprite.set_visible(false);
    }
}

void Arrow::reset()
{
    v_states[state]->reset();
    state = States::calm;
    distance = 0.0;
    count_of_targets = 0;
}

void Arrow::shot(const Vector2 p_direction)
{
    reset();
    state = States::fly;
    direction = p_direction;
}