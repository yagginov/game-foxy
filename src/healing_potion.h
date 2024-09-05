#ifndef HEALING_POTION_H
#define HEALING_POTION_H

#include "item.h"

namespace godot {

class HealingPotion : public Item 
{
    GDCLASS(HealingPotion, Item);

protected:
    static void         _bind_methods();

private:
    int                 hp;

public:
    HealingPotion();
    ~HealingPotion();

    bool                use_item() override;

    void                set_hp(const int p_hp);
    int                 get_hp() const;

};

}           // namespace godot

#endif      // HEALING_POTION_H
