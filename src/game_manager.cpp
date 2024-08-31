#include "game_manager.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "main_character.h"

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

} // namespace godot
