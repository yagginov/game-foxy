#include "health_ui.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "game_manager.h"
#include "main_character.h"
#include "components/health_component.h"

using namespace godot;

void HealthUI::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_container_path"), &HealthUI::get_container_path);
	ClassDB::bind_method(D_METHOD("set_container_path", "p_container_path_path"), &HealthUI::set_container_path);
	ClassDB::add_property("HealthUI", PropertyInfo(Variant::NODE_PATH, "container_path"), "set_container_path", "get_container_path");

    ClassDB::bind_method(D_METHOD("_change_health", "hp"), &HealthUI::_change_health);

}

HealthUI::HealthUI() 
{
    container = nullptr;
}

HealthUI::~HealthUI() 
{
    
}

void HealthUI::_ready() 
{
    add_to_group("UI");

    if (has_node(container_path)) 
    {
        container = get_node<GridContainer>(container_path);
    }

    if (has_node("../HealthComponent"))
    {
        HealthComponent* hc = get_node<HealthComponent>("../HealthComponent");
        hc->connect("change_health", Callable(this, "_change_health"));
        for (int i = 0; i < (int)(hc->get_max_hp()); ++i)
        {
            add_panel_with_sprite();
        }

        if (container)
        {
            container->set_columns((int)(hc->get_max_hp()));
        }
        
    }
    
}

void HealthUI::_physics_process(double delta)
{

}

void HealthUI::add_panel_with_sprite()
{
    Panel *new_panel = memnew(Panel);
    new_panel->set_name("Panel");
    new_panel->set_custom_minimum_size(Vector2(16, 16));
    new_panel->set_self_modulate(Color(0.0, 0.0, 0.0, 0.0));

    Sprite2D *new_sprite = memnew(Sprite2D);
    new_sprite->set_centered(false);
    Ref<Texture2D> texture = ResourceLoader::get_singleton()->load("res://assets/sprites/heart_sprites.png");
    new_sprite->set_texture(texture);
    new_sprite->set_hframes(2);
    new_sprite->set_frame(0);

    new_panel->add_child(new_sprite);
    container->add_child(new_panel);

    panels.push_back(new_panel);
    health_sprites.push_back(new_sprite);

}

void HealthUI::_change_health(double hp)
{
    int i_hp = (int)hp;
    if (health_sprites.size() < i_hp)
    {
        for(int i = 0; i < i_hp - health_sprites.size(); ++i)
        {
            add_panel_with_sprite();
        }

        container->set_columns(i_hp);
    }

    for (auto& it : health_sprites)
    {
        if (i_hp)
        {
            it->set_frame(0);
            --i_hp;
        }
        else
        {
            it->set_frame(1);
        }        
    }
}


void HealthUI::set_container_path(const NodePath& p_container_path)
{
    container_path = p_container_path;
}
NodePath HealthUI::get_container_path() const
{
    return container_path;
}
