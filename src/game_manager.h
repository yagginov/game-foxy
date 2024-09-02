#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class MainCharacter;
class Item;
class Slot;

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

    Slot* from_slot;
    Ref<Item> item;
    Sprite2D* mouse_item_sprite;

public:
    void _ready() override;
    void _physics_process(double delta) override;
    //void _physics_frame();

    void give_mc_pointer(MainCharacter* p_mc);

    bool is_input_allowed() const;
    void set_input_allowed(const bool p_input_allowed);

    Node* get_current_scene() const;
	Vector2 get_mouse_position() const;

    void spawn_liftable_object(Ref<Item>& item, Vector2 position, Vector2 impulse, String velocity_component_path);

    void start_drag(Slot* p_from_slot, const Ref<Item> p_item);
    void end_drag(Slot* to_slot);

    bool is_item_valid() const;

};

} // namespace godot

#endif // GAME_MANAGER_H
