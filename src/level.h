#ifndef LEVEL_H
#define LEVEL_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "game_manager.h"

namespace godot {

class Level : public Node2D {
    GDCLASS(Level, Node2D)

protected:
    static void _bind_methods();

private:
    GameManager* gm;
    String name;
    String scene_path;

public:
    Level();
    ~Level();

    void _ready() override;

    void set_name(const String& p_name);
    String get_name() const;

    void set_scene_path(const String& p_scene_path);
    String get_scene_path() const;

    Dictionary save();
    void load(const Dictionary& info);

};

} // namespace godot

#endif // LEVEL_H
