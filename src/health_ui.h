#ifndef HEALTH_UI_H
#define HEALTH_UI_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/grid_container.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/panel.hpp>

#include <godot_cpp/templates/vector.hpp>


namespace godot {

class HealthUI : public Control {
    GDCLASS(HealthUI, Control)

protected:
    static void _bind_methods();

private:

    GridContainer*      container;
    NodePath            container_path;

    Vector<Panel*>      panels;
    Vector<Sprite2D*>   health_sprites;


private:
    void add_panel_with_sprite();

public:
    HealthUI();
    ~HealthUI();

    void _ready();
    void _physics_process(double delta) override;

    void _change_health(double hp);

    // set / get
    void            set_container_path(const NodePath& p_container_path);
    NodePath        get_container_path() const;

    void            set_first_health_sprite_path(const NodePath& p_first_health_sprite_path);
    NodePath        get_first_health_sprite_path() const;

};          // class HealthUI

}           // namespace godot

#endif      // HEALTH_UI_H
