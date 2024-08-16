#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "main_character.h"

namespace godot {

class MainCharacter;

class GameManager : public Node2D {
    GDCLASS(GameManager, Node2D)

    

protected:
    static void _bind_methods();

public:
    static GameManager *singleton;
    static GameManager *get_singleton();

protected:
    ~GameManager();

private:

public:
    MainCharacter* get_mc() const;

};

} // namespace godot

#endif // GAME_MANAGER_H
