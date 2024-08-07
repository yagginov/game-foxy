#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <godot_cpp/classes/animated_sprite2d.hpp>

#include "components_container.h"

namespace godot {

class GameObject : public AnimatedSprite2D {
    GDCLASS(GameObject, AnimatedSprite2D);

protected:
    static void _bind_methods();

private:

public:
    GameObject();
    ~GameObject();

    void _ready() override;
    void _physics_process(double delta) override;

    void _damage(Vector2 enemy_pos);

};

}           // namespace godot

#endif      // GAME_OBJECT_H
