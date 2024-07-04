#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>


#include "actor.h"
#include "main_character.h"

#include "animation_controller.h"

#include "baseEnemy.h"
#include "DummyEnemy.h"
#include "LittleBoar.h"


#include "health_component.h"
#include "hurtbox.h"
#include "hitbox.h"

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// Actors:
	GDREGISTER_CLASS(Actor);
	GDREGISTER_CLASS(MainCharacter);

	// Components:
	GDREGISTER_CLASS(AnimationController);
	GDREGISTER_CLASS(HealthComponent);
	GDREGISTER_CLASS(Hurtbox);
	GDREGISTER_CLASS(Hitbox);

	// Enemys:
	GDREGISTER_CLASS(DummyEnemy);
	GDREGISTER_CLASS(BaseEnemy);
	GDREGISTER_CLASS(LittleBoar);

}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}