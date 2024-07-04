#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot
{

class Actor : public CharacterBody2D {
	GDCLASS(Actor, CharacterBody2D)

protected:
	static void _bind_methods();

protected:
    Vector2 velocity;

private:
    size_t index;
    double speed;
    double acceleration;

public:
	Actor();
	~Actor();

	void _ready() override;

    void move(const Vector2& direction, double delta);

    void set_speed(const double p_speed);
    double get_speed() const;

    void set_acceleration(const double p_acceleration);
    double get_acceleration() const;
};

}   // namespace godot


#endif // ACTOR_H 