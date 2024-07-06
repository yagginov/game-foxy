#ifndef SEARCH_AREA_H
#define SEARCH_AREA_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>

#include "actor.h"

namespace godot {

class SearchArea : public Area2D {
	GDCLASS(SearchArea, Area2D)

protected:
	static void _bind_methods();

private:
    Actor* target;

    NodePath ray_cast_path;
    RayCast2D* ray_cast;

public:
	SearchArea();
	~SearchArea();

	void _ready() override;
    void _physics_process(double delta) override;

    void _target_entered(Actor* node);
    void _target_exited(Actor* node);

    void set_ray_cast(const NodePath& p_ray_cast);
    NodePath get_ray_cast() const;

};

}	// namespace godot

#endif // SEARCH_AREA_H