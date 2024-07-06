#include "search_area.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void SearchArea::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_ray_cast"), &SearchArea::get_ray_cast);
	ClassDB::bind_method(D_METHOD("set_ray_cast", "p_ray_cast"), &SearchArea::set_ray_cast);
	ClassDB::add_property("SearchArea", PropertyInfo(Variant::NODE_PATH, "ray_cast"), "set_ray_cast", "get_ray_cast");

    ClassDB::bind_method(D_METHOD("_target_entered"), &SearchArea::_target_entered);
    ClassDB::bind_method(D_METHOD("_target_exited"), &SearchArea::_target_exited);

    ADD_SIGNAL(MethodInfo("target_spotted", PropertyInfo(Variant::VECTOR2, "target_pos")));
    ADD_SIGNAL(MethodInfo("target_missed"));
}

SearchArea::SearchArea()
{
    target = nullptr;
    ray_cast = nullptr;
}

SearchArea::~SearchArea()
{

}

void SearchArea::_ready()
{
    if (has_node(ray_cast_path)) {
        ray_cast = get_node<RayCast2D>(ray_cast_path); 
    }

    this->connect("body_entered", Callable(this, "_target_entered"));
    this->connect("body_exited", Callable(this, "_target_exited"));
}

void SearchArea::_physics_process(double delta)
{
    if (target)
    {
        Vector2 target_pos = target->get_global_position();
        ray_cast->set_target_position(target_pos - get_global_position());
        ray_cast->force_raycast_update();

        if (!ray_cast->is_colliding())
        {
            emit_signal("target_spotted", target_pos);
        }
        else
        {
            emit_signal("target_missed");
        }
    }
}


void SearchArea::_target_entered(Actor* node)
{
    target = node;
    ray_cast->add_exception(node);

    UtilityFunctions::print("target_entered");
}

void SearchArea::_target_exited(Actor* node)
{
    target = nullptr;
    ray_cast->remove_exception(node);
    emit_signal("target_missed");

    UtilityFunctions::print("target_missed");
}

void SearchArea::set_ray_cast(const NodePath& p_ray_cast)
{
    ray_cast_path = p_ray_cast;
}

NodePath SearchArea::get_ray_cast() const
{
    return ray_cast_path;
}