#ifndef ARROW_H
#define ARROW_H

#include "components/hitbox.h"
#include "state.h"
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/templates/vector.hpp>


namespace godot {

class Arrow: Hitbox
{
    GDCLASS(Arrow, Hitbox);

protected:
	static void _bind_methods();

private:
    enum States 
    {
        calm = 0, 
        fly = 1
    }

private:
    // elements
    int                 max_count_of_targets;
    int                 count_of_targets;

    NodePath            sprite_path;
    Sprite2D            sprite;

    double              max_distance;
    double              distance;
    Vector2             prev_position;
    Vector2             direction;

    Vector<State*>       v_states;
    States              state;

public:
    Arrow();
	~Arrow();

	void _ready() override;
    void _physics_process(double delta) override;

    void f_fly(double delta);

    void hit(Vector2 target_pos) override;

    void turn_on() override;
    void turn_off() override;

    void shot(const Vector2 p_direction);
    void reset();

    // set / get
    void set_sprite_path(const NodePath& p_sprite_path);
    NodePath get_sprite_path() const;

    void set_max_count_of_targets(const int p_max_count_of_targets);
    int get_max_count_of_targets() const;

    void set_max_distance(const double p_max_distance);
    double get_max_distance() const;

    
}   // class Arrow


}	// namespace godot

#endif	// ARROW_H