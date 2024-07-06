#ifndef HURTBOX_H
#define HURTBOX_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>

#include "hitbox.h"
#include "health_component.h"


namespace godot {

class Hurtbox : public Area2D {
	GDCLASS(Hurtbox, Area2D)

protected:
	static void _bind_methods();

private:
    NodePath health_path;
    HealthComponent* health;

public:
	Hurtbox();
	~Hurtbox();

	void _ready() override;

    void _hitbox_entered(Hitbox* node);

    void set_health(const NodePath& p_health);
    NodePath get_health() const;

};

}	// namespace godot

#endif // HURTBOX_H