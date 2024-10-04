#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "components/health_component.h"
#include "components/hurtbox.h"

namespace godot
{

class Actor : public CharacterBody2D {
	GDCLASS(Actor, CharacterBody2D)

protected:
	static void _bind_methods();

protected:
    Vector2 velocity;

private:
    int index;
    double speed;
    double acceleration;

public:
	Actor();
	~Actor();

	void _ready() override;

    void move(const Vector2& direction, double delta);
    virtual void _damage(Vector2 enemy_pos);
    virtual void _dead();

    void set_index(const int p_index);
    int get_index() const;

    void set_speed(const double p_speed);
    double get_speed() const;

    void set_acceleration(const double p_acceleration);
    double get_acceleration() const;

    virtual Dictionary save();
    virtual void load(const Dictionary& info);
};

}   // namespace godot


#endif // ACTOR_H 