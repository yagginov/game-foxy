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

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/json.hpp>

#include "main_character.h"
#include "item.h"
#include "liftable_object.h"
#include "slot.h"
#include "level.h"

namespace godot {

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::get_singleton() {
    return instance;
}

void GameManager::set_instance(GameManager* p_instance)
{
    instance = p_instance;
}

void GameManager::_bind_methods()
{
	ClassDB::bind_static_method(GameManager::get_class_static(), D_METHOD("get_singleton"), &GameManager::get_singleton, DEFVAL(nullptr));
	ClassDB::bind_static_method(GameManager::get_class_static(), D_METHOD("set_instance", "p_instance"), &GameManager::set_instance, DEFVAL(nullptr));
}


GameManager::GameManager():
input_allowed(true),
item(nullptr),
from_slot(nullptr),
mouse_item_sprite(memnew(Sprite2D))
{
    i = Input::get_singleton();
}

GameManager::~GameManager() 
{

}

void GameManager::_ready()
{
    instance = this;
    
    mouse_item_sprite->set_centered(true);
    mouse_item_sprite->set_z_index(4);
    add_child(mouse_item_sprite);

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
    
    if (i->is_physical_key_pressed(KEY_L))
    {
        save();
    }
}



void GameManager::give_mc_pointer(MainCharacter* p_mc)
{
    mc = p_mc;
}

void GameManager::give_current_level(Level* p_current_level)
{
    current_level = p_current_level;
    levels[current_level->get_name()] = current_level->save();
    load();
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
    item_count = from_slot->get_item_count();

    mouse_item_sprite->set_texture(item->get_texture());
}

void GameManager::end_drag(Slot* to_slot)
{
    if (!to_slot->is_empty())
    {
        if (to_slot->get_item()->get_name() == item->get_name())
        {
            if (!to_slot->add_item(item_count))
            {
                from_slot->set_item(item);
                if (--item_count)
                {
                    from_slot->add_item(item_count);
                }
                from_slot->update();
            }
            to_slot->update();
            mouse_item_sprite->set_texture(nullptr);
            item.unref();
            from_slot = nullptr;
            item_count = 0;
            return;
        }
        else
        {
            from_slot->set_item(to_slot->get_item());
            size_t count = to_slot->get_item_count() - 1;
            if(count) 
            {
                from_slot->add_item(count);
            }
            from_slot->update();
        }
    }
    to_slot->set_item(item);
    if (--item_count)
    {
        to_slot->add_item(item_count);
    }
    to_slot->update();

    mouse_item_sprite->set_texture(nullptr);
    item.unref();
    from_slot = nullptr;
    item_count = 0;
}

bool GameManager::is_item_valid() const
{
    return item.is_valid();
}

void GameManager::save()
{
    Dictionary info;

    info["MC"] = mc->save();
    
    if (current_level)
    {
        levels[current_level->get_name()] = current_level->save();
    }
    info["levels"] = levels;

    Ref<FileAccess> file = FileAccess::open(String("save.json"), FileAccess::WRITE);
    if (file.is_valid())
    {
        String json_data = JSON::stringify(info, "    ");
        file->store_string(json_data);
        file->close();
    }

}

Dictionary GameManager::load_file(const String& file_path)
{
    Dictionary save_data;

    Ref<FileAccess> file = FileAccess::open(file_path, FileAccess::READ);
    if (file.is_null()) 
    {
        ERR_PRINT("Cannot open file: " + file_path);
        return save_data;
    }

    String json_content = file->get_as_text();
    file->close();
    
    Variant parse_result;

    parse_result = JSON::parse_string(json_content);
    
    if (parse_result.get_type() == Variant::DICTIONARY) 
    {
        save_data = parse_result;
    } 
    else 
    {
        ERR_PRINT("Parsed JSON is not a Dictionary.");
    }

    return save_data;
}

void GameManager::load()
{
    Dictionary info = load_file("save.json");

    if (info.has("MC"))
    {
        if (info["MC"].get_type() == Variant::DICTIONARY)
        {
            Dictionary mc_info = info["MC"];
            mc->load(mc_info);
        }
    }

    if (info.has("levels"))
    {
        if (info["levels"].get_type() == Variant::DICTIONARY)
        {
            Dictionary levels_info = info["levels"];

            if (levels_info.has(current_level->get_name()))
            {
                if (levels_info[current_level->get_name()].get_type() == Variant::DICTIONARY)
                {
                    Dictionary current_level_info = levels_info[current_level->get_name()];
                    current_level->load(current_level_info);
                }
            }
        }
    }

}

} // namespace godot
