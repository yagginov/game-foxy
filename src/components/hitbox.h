#ifndef HITBOX_H
#define HITBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/collision_polygon2d.hpp>

#include <godot_cpp/variant/vector2.hpp>


namespace godot {

class Hitbox : public Area2D {
	GDCLASS(Hitbox, Area2D)

protected:
	static void _bind_methods();

private:
    double damage;
    CollisionPolygon2D* colliding_box;
    
    NodePath colliding_box_path;

public:
	Hitbox();
	~Hitbox();

	void _ready() override;

    void hit(Vector2 target_pos);

    void turn_on();
    void turn_off();

    void set_damage(const double p_damage);
    double get_damage() const;

    void set_colliding_box_path(const NodePath& p_colliding_box_path);
    NodePath get_colliding_box_path() const;

};

}	// namespace godot

#endif // HITBOX_H