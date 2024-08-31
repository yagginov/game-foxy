#include "game_manager.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "main_character.h"
#include "item.h"
#include "liftable_object.h"

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
input_allowed(true)
{
    i = Input::get_singleton();
}

GameManager::~GameManager() {
    if (singleton == this) {
        ClassDB::_unregister_engine_singleton(GameManager::get_class_static());
        singleton = nullptr;
    }
}

void GameManager::create_singletone()
{
    singleton = memnew(GameManager);
}

void GameManager::_ready()
{
    
}

void GameManager::give_mc_pointer(MainCharacter* p_mc)
{
    mc = p_mc;
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

} // namespace godot
