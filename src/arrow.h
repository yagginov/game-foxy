#ifndef ARROW_H
#define ARROW_H

#include "components/hitbox.h"
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/node2d.hpp>


namespace godot {

class Arrow: Hitbox
{
    GDCLASS(Arrow, Hitbox);

protected:
	static void _bind_methods();

private:
    // elements
    int                 max_count_of_targets;
    int                 count_of_targets;

    NodePath            sprite_path;
    Sprite2D            sprite;

public:
    Arrow();
	~Arrow();

	void _ready() override;

    void hit(Vector2 target_pos) override;

    void turn_on() override;
    void turn_off() override;

    void set_sprite_path(const NodePath& p_sprite_path);
    NodePath get_sprite_path() const;

    
}   // class Arrow


}	// namespace godot

#endif	// ARROW_H