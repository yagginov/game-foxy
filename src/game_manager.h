#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "main_character.h"

namespace godot
{

class GameManager : public Node2D 
{
    GDCLASS(GameManager, Node2D);

protected:
    static void _bind_methods();

private:
    static GameManager*         instance;
    GameManager () 
    {
        MC = nullptr;
    }

private:
    NodePath                    main_character_path;
    MainCharacter*              MC;

public:


    // Get the singleton instance
    static GameManager*         get_singleton()
    {
        if (instance == nullptr) 
        {
            instance = memnew(GameManager);
        }
        return instance;
    }
    
    // Initialize the singleton (used by Godot to register the class as a singleton)
    static void                 _register_singleton() 
    {
        instance = memnew(GameManager);
        Engine::get_singleton()->register_singleton("GameManager", instance);
    }

    void                        _ready() override;

    MainCharacter*              get_main_character() const;

    NodePath                    get_main_character_path() const;
    void                        set_main_character_path(const NodePath p_MC);

};          // class GameManager

}           // namespace godot

#endif      // GAMEMANAGER_H
