#ifndef HITBOX_H
#define HITBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/collision_polygon2d.hpp>


namespace godot {

class Hitbox : public Area2D {
	GDCLASS(Hitbox, Area2D)

protected:
	static void _bind_methods();

private:
    double damage;
    CollisionPolygon2D* colliding_box;

public:
	Hitbox();
	~Hitbox();

	void _ready() override;

    void turn_on();
    void turn_off();

    void set_damage(const double p_damage);
    double get_damage() const;

};

}	// namespace godot

#endif // HITBOX_H