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
	
}

Arrow::~Arrow() 
{
	// Add your cleanup here.

}

void Arrow::_ready() {
	add_to_group("Arrow");

}

void Arrow::hit(Vector2 target_pos)
{
    Hitbox::hit(target_pos);
}

void Arrow::turn_on()
{
    Hitbox::turn_on();
    texture.set_visible(true);
}

void Arrow::turn_off()
{
    Hitbox::turn_off();
    texture.set_visible(false);
}