#ifndef COMPONENTS_CONTAINER_H
#define COMPONENTS_CONTAINER_H

#include <godot_cpp/classes/node2d.hpp>

#include "actor.h"

#include "components/health_component.h"
#include "components/hitbox.h"
#include "components/hurtbox.h"
#include "components/animation_controller.h"
#include "components/search_area.h"

namespace godot {

class ComponentsContainer : public Node2D {
	GDCLASS(ComponentsContainer, Node2D)

protected:
	static void _bind_methods();

private:
    NodePath health_path;
    NodePath hitbox_path;
    NodePath hurtbox_path;
    NodePath animation_controller_path;
    NodePath search_area_path;
    

public:
    HealthComponent* health;
    Hitbox* hitbox;
    Hurtbox* hurtbox;
    AnimationController* animation_controller;
    SearchArea* search_area;

public:
	ComponentsContainer();
	~ComponentsContainer();

	void _ready() override;
    void bind(Actor* mother_pointer);

    void set_health_path(const NodePath& p_health_path);
    NodePath get_health_path() const;

    void set_hitbox_path(const NodePath& p_hitbox_path);
    NodePath get_hitbox_path() const;

    void set_hurtbox_path(const NodePath& p_hurtbox_path);
    NodePath get_hurtbox_path() const;

    void set_animation_controller_path(const NodePath& p_animation_controller_path);
    NodePath get_animation_controller_path() const;

    void set_search_area_path(const NodePath& p_search_area_path);
    NodePath get_search_area_path() const;
};

}	// namespace godot

#endif // COMPONENTS_CONTAINER_H