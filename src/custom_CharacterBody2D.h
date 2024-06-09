#ifndef CUSTOM_CHARACTER_BODY2D_H_H
#define CUSTOM_CHARACTER_BODY2D_H_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot {

class CustomCharacterBody2D : public CharacterBody2D {
	GDCLASS(CustomCharacterBody2D, CharacterBody2D)

private:
	Input* i;
	double hp_helper, stamina_helper, mp_helper;

public:
	double speed;
	int hp, stamina, mp;
	int max_hp, max_stamina, max_mp;

protected:
	static void _bind_methods();

public:
	CustomCharacterBody2D();
	~CustomCharacterBody2D();

	void _process(double delta) override;
	void _physics_process(double delta) override;
	
	void set_speed(const double p_speed);
	double get_speed() const;


	void set_hp(const int p_hp);
	int get_hp() const;

	void set_stamina(const int p_stamina);
	int get_stamina() const;

	void set_mp(const int p_mp);
	int get_mp() const;


	void set_max_hp(const int p_max_hp);
	int get_max_hp() const;

	void set_max_stamina(const int p_max_stamina);
	int get_max_stamina() const;

	void set_max_mp(const int p_max_mp);
	int get_max_mp() const;

	inline void hp_recovery();
	inline void stamina_recovery();
	inline void mp_recovery();
};

}

#endif