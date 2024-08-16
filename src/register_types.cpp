#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

// characters
#include "actor.h"
#include "main_character.h"
#include "dummy_enemy.h"
#include "boar.h"
#include "bat.h"
#include "dagger_goblin.h"

// components
#include "components/animation_controller.h"
#include "components/health_component.h"
#include "components/hurtbox.h"
#include "components/hitbox.h"
#include "components/search_area.h"
#include "components_container.h"

#include "arrow.h"

// ui
#include "main_menu.h"
#include "pause_menu.h"

// inventory system
#include "inventory.h"
#include "item.h"
#include "healing_potion.h"

// game manager
#include "game_manager.h"

//
#include "non_playable_character.h"
//


using namespace godot;

void initialize_game_foxy_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// Actors:
	GDREGISTER_CLASS(Actor);
	GDREGISTER_CLASS(MainCharacter);
	GDREGISTER_CLASS(NPC);

	// Components:
	GDREGISTER_CLASS(AnimationController);
	GDREGISTER_CLASS(HealthComponent);
	GDREGISTER_CLASS(Hurtbox);
	GDREGISTER_CLASS(Hitbox);
	GDREGISTER_CLASS(SearchArea);
	GDREGISTER_CLASS(ComponentsContainer);

	GDREGISTER_CLASS(Arrow);

	// Enemys:
	GDREGISTER_CLASS(DummyEnemy);
	GDREGISTER_CLASS(Boar);
	GDREGISTER_CLASS(Bat);
	GDREGISTER_CLASS(DaggerGoblin);

	// UI
	GDREGISTER_CLASS(MainMenu);
	GDREGISTER_CLASS(PauseMenu);

	// Inventory System
	GDREGISTER_CLASS(Inventory);
	GDREGISTER_CLASS(Item);
	GDREGISTER_CLASS(HealingPotion);

	// Game Manager
	GDREGISTER_CLASS(GameManager);
	godot::GameManager::singleton = memnew(godot::GameManager);
    Engine::get_singleton()->register_singleton("GameManager", godot::GameManager::singleton);

}

void uninitialize_game_foxy_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT game_foxy_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_game_foxy_module);
	init_obj.register_terminator(uninitialize_game_foxy_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}