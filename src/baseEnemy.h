#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

class BaseEnemy : public CharacterBody2D {
	GDCLASS(BaseEnemy, CharacterBody2D)

public:
	double speed;
	double pixels_in_meter;
	double hp;
	double attack;

	double knockback_time;
	Vector2 knockback;

protected:
	static void _bind_methods();

public:
    BaseEnemy();
	~BaseEnemy();

    virtual void take_damage(int amount);

    void set_speed(const double p_speed);
	double get_speed() const;

	void set_pixels_in_meter(const double p_pixels_in_meter);
	double get_pixels_in_meter() const;

    void set_hp(const double p_hp);
	double get_hp() const;

	void set_attack(const double p_attack);
	double get_attack() const;

};

}

#endif