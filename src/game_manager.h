#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node2d.hpp>

namespace godot {

class MainCharacter;

class GameManager : public Node2D {
    GDCLASS(GameManager, Node2D)

private:
    GameManager();

protected:
    static void _bind_methods();

public:
    static GameManager *singleton;
    static GameManager *get_singleton();
    static void create_singletone();

protected:
    ~GameManager();

public:
    Input* i;
    MainCharacter* mc;

private:
    bool input_allowed;

public:
    void _ready() override;

    void give_mc_pointer(MainCharacter* p_mc);
    MainCharacter* get_mc() const;

    bool is_input_allowed() const;
    void set_input_allowed(const bool p_input_allowed);

    Node* get_current_scene() const;

};

} // namespace godot

#endif // GAME_MANAGER_H
