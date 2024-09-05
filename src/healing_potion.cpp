#include "healing_potion.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "main_character.h"
#include "components/health_component.h"

using namespace godot;

void HealingPotion::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_hp"), &HealingPotion::get_hp);
	ClassDB::bind_method(D_METHOD("set_hp", "p_hp"), &HealingPotion::set_hp);
	ClassDB::add_property("HealingPotion", PropertyInfo(Variant::INT, "hp"), "set_hp", "get_hp");
}

HealingPotion::HealingPotion() : Item::Item()
{
    set_name("HealingPotion");
    hp = 2;
}

HealingPotion::~HealingPotion() 
{
    // Add your cleanup here.
}


bool HealingPotion::use_item()
{
    Item::use_item();
    if (gm->mc)
    {
        HealthComponent* hc = gm->mc->get_node<HealthComponent>("HealthComponent");
        if (hc)
        {
            if (hc->get_hp() == hc->get_max_hp())
            {
                return false;
            }
            else
            {
                hc->heal(hp);
                return true;
            }
        }
    }
    return false;
}


void HealingPotion::set_hp(const int p_hp)
{
    hp = p_hp;
}
int HealingPotion::get_hp() const
{
    return hp;
}