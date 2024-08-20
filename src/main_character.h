#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/classes/line_edit.hpp>

#include "actor.h"
#include "state.h"
#include "components/animation_controller.h"
#include "components/hitbox.h"
#include "components_container.h"

#include "inventory.h"

#include "game_manager.h"

/**/
#include "arrow.h"
/**/

namespace godot {

class MainCharacter : public Actor {
	GDCLASS(MainCharacter, Actor)

enum States
{
	idle = 0,
	run = 1,
	slide = 2,
	attack = 3,
	shot = 4
};

const Vector2 VECTOR2_ZERO = Vector2(0.0, 0.0);

protected:
	static void _bind_methods();

private:
	GameManager* gm;

	Input* i;
	Vector2 direction;

	States state;
	Vector<State*> v_states;

	ComponentsContainer* components;
	Sprite2D* sword;

	Arrow* arrow;

	LineEdit* arrow_line;

	Inventory* inventory;

private:
	Vector2 get_mouse_position() const;


public:
	MainCharacter();
	~MainCharacter();

    void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void f_idle(double delta);
	void f_run(double delta);
	void f_slide(double delta);
	void f_attack(double delta);
	void f_shot(double delta);

	void _damage(Vector2 enemy_pos) override;
	void _dead();
	void _hit(Vector2 target_pos);

	void change_state(States state);
};

}	// namespace godot

#endif	// MAIN_CHARACTER_H