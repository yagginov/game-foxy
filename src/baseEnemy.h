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

protected:
	static void _bind_methods();

public:
    BaseEnemy();
	~BaseEnemy();

    void _ready() override;
	void _process(double delta) override;

    void take_damage(int amount);

    void set_speed(const double p_speed);
	double get_speed() const;

	void set_pixels_in_meter(const double p_pixels_in_meter);
	double get_pixels_in_meter() const;

    void set_hp(const double p_hp);
	double get_hp() const;

};

}

#endif