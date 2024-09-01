#include "game_manager.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/window.hpp>

#include "main_character.h"
#include "item.h"
#include "liftable_object.h"
#include "slot.h"

namespace godot {

GameManager* GameManager::singleton = nullptr;

GameManager* GameManager::get_singleton() {
    if (unlikely(singleton == nullptr)) {
        GDExtensionObjectPtr singleton_obj = internal::gdextension_interface_global_get_singleton(GameManager::get_class_static()._native_ptr());
        #ifdef DEBUG_ENABLED
        ERR_FAIL_NULL_V(singleton_obj, nullptr);
        #endif // DEBUG_ENABLED
        singleton = reinterpret_cast<GameManager*>(internal::gdextension_interface_object_get_instance_binding(singleton_obj, internal::token, &GameManager::_gde_binding_callbacks));
        #ifdef DEBUG_ENABLED
        ERR_FAIL_NULL_V(singleton, nullptr);
        #endif // DEBUG_ENABLED
        if (likely(singleton)) {
            ClassDB::_register_engine_singleton(GameManager::get_class_static(), singleton);
        }
    }
    return singleton;
}

void GameManager::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_mc"), &GameManager::get_mc);
}


GameManager::GameManager():
input_allowed(true),
item(nullptr),
from_slot(nullptr),
mouse_item_sprite(memnew(Sprite2D))
{
    i = Input::get_singleton();
    //get_tree()->get_root()->add_child(this);
}

GameManager::~GameManager() {
    //if (singleton == this) {
        //ClassDB::_unregister_engine_singleton(GameManager::get_class_static());
        //singleton = nullptr;
    //}
}

void GameManager::create_singletone()
{
    singleton = memnew(GameManager);
}

void GameManager::_ready()
{
}


void GameManager::_physics_process(double delta)
{
    if (item.is_valid())
    {
        mouse_item_sprite->set_global_position(get_mouse_position());
        input_allowed = false;

        if (i->is_physical_key_pressed(KEY_R))
        {
            Vector2 direction = (get_mouse_position() - mc->get_global_position()).normalized();

            spawn_liftable_object(item, mc->get_global_position(), direction * 50, "res://resources/drop_item_velocity_component.tres");

            from_slot = nullptr;
            mouse_item_sprite->set_texture(nullptr);
            input_allowed = true;
        }
    }
    else
    {
        input_allowed = true;
    }
    
}

void GameManager::create_mc()
{
    //Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://scenes/mc.tscn");
    
    //if (scene.is_valid()) 
    //{
    //    mc = Object::cast_to<MainCharacter>(scene->instantiate());
    //}

    //mc = get_node<MainCharacter>("./MC"); 
}


void GameManager::give_mc_pointer(MainCharacter* p_mc)
{
    mc = p_mc;
    if (mouse_item_sprite->get_parent() != mc->get_node<Node2D>("."))
    {
        mc->get_node<Node2D>(".")->add_child(mouse_item_sprite);
    }
    if (singleton->get_parent() != mc->get_node<Node2D>("."))
    {
        mc->get_node<Node2D>(".")->add_child(singleton);
    }
    //get_node<Node2D>(".")->add_child(this);
    mouse_item_sprite->set_centered(true);
    mouse_item_sprite->set_z_index(4);
    
}


MainCharacter* GameManager::get_mc() const
{
    return mc;
}

bool GameManager::is_input_allowed() const
{
    return input_allowed;
}
void GameManager::set_input_allowed(const bool p_input_allowed)
{
    input_allowed = p_input_allowed;
}

Node* GameManager::get_current_scene() const
{
    return mc->get_tree()->get_current_scene();
}

Vector2 GameManager::get_mouse_position() const
{
	return get_global_mouse_position();
}

void GameManager::spawn_liftable_object(Ref<Item>& item, Vector2 position, Vector2 impulse, String velocity_component_path) 
{
    // Load liftable_object
    Ref<PackedScene> liftable_object_scene = ResourceLoader::get_singleton()->load("res://scenes/liftable_object.tscn");
    LiftableObject* liftable_object_instance = Object::cast_to<LiftableObject>(liftable_object_scene->instantiate());

    // Load velocity_component for liftable_object
    Ref<VelocityComponent> velocity_component = ResourceLoader::get_singleton()->load(velocity_component_path);
    velocity_component->set_impulse(impulse);

    // Set basic data for liftable_object
    liftable_object_instance->set_velocity_component(velocity_component);
    liftable_object_instance->set_item(item);
    liftable_object_instance->set_global_position(position);

    // Load and add liftable_object to current scene
    Node *current_scene = get_current_scene();
    if (current_scene) 
    {
        current_scene->add_child(liftable_object_instance);
    } 

    item.unref();
}

void GameManager::start_drag(Slot* p_from_slot, const Ref<Item> p_item)
{
    input_allowed = false;
    from_slot = p_from_slot;
    item = p_item;

    mouse_item_sprite->set_texture(item->get_texture());
}

void GameManager::end_drag(Slot* to_slot)
{
    if (!to_slot->is_empty())
    {
        from_slot->set_item(to_slot->get_item());
    }
    to_slot->set_item(item);

    mouse_item_sprite->set_texture(nullptr);
    item.unref();
    from_slot = nullptr;
}

bool GameManager::is_item_valid() const
{
    return item.is_valid();
}

} // namespace godot
