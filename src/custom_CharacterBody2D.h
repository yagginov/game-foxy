#ifndef CUSTOM_CHARACTER_BODY2D_H_H
#define CUSTOM_CHARACTER_BODY2D_H_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {

class CustomCharacterBody2D : public CharacterBody2D {
	GDCLASS(CustomCharacterBody2D, CharacterBody2D)

private:
	Input* i;
	bool sprint_helper;

public:
	double speed;
	double hp, stamina, mp;
	double max_hp, max_stamina, max_mp;
	double rs_hp, rs_stamina, rs_mp; // rs - recovery speed; default = 1 point in second

protected:
	static void _bind_methods();

public:
	CustomCharacterBody2D();
	~CustomCharacterBody2D();

	void _process(double delta) override;
	void _physics_process(double delta) override;
	
	void set_speed(const double p_speed);
	double get_speed() const;


	void set_hp(const double p_hp);
	double get_hp() const;

	void set_stamina(const double p_stamina);
	double get_stamina() const;

	void set_mp(const double p_mp);
	double get_mp() const;


	void set_max_hp(const double p_max_hp);
	double get_max_hp() const;

	void set_max_stamina(const double p_max_stamina);
	double get_max_stamina() const;

	void set_max_mp(const double p_max_mp);
	double get_max_mp() const;


	void set_rs_hp(const double p_rs_hp);
	double get_rs_hp() const;

	void set_rs_stamina(const double p_rs_stamina);
	double get_rs_stamina() const;

	void set_rs_mp(const double p_rs_mp);
	double get_rs_mp() const;


	inline void hp_recovery(double delta);
	inline void stamina_recovery(double delta);
	inline void mp_recovery(double delta);
};

}

#endif