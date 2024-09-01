#ifndef LEVEL_H
#define LEVEL_H

#include <godot_cpp/classes/node2d.hpp>

#include "game_manager.h"

namespace godot {

class Level : public Node2D {
    GDCLASS(Level, Node2D)

protected:
    static void _bind_methods();

private:
    GameManager* gm;

public:
    Level();
    ~Level();

    void _ready() override;

};

} // namespace godot

#endif // LEVEL_H
