#include "healing_potion.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "components/health_component.h"

using namespace godot;

void HealingPotion::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_hp"), &HealingPotion::get_hp);
	ClassDB::bind_method(D_METHOD("set_hp", "p_hp"), &HealingPotion::set_hp);
	ClassDB::add_property("HealingPotion", PropertyInfo(Variant::INT, "hp"), "set_hp", "get_hp");
}

HealingPotion::HealingPotion() 
{

}

HealingPotion::~HealingPotion() 
{
    // Add your cleanup here.
}

void HealingPotion::_ready() 
{
    Item::_ready();
}

void HealingPotion::_physics_process(double delta) 
{
    
}


void HealingPotion::use_item()
{
    gm->get_main_character()->get_node<HealthComponent>("HealthComponent")->heal(hp);
}


void HealingPotion::set_hp(const int p_hp)
{
    hp = p_hp;
}
int HealingPotion::get_hp() const
{
    return hp;
}