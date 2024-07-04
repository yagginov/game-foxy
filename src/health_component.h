#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>


namespace godot {

class HealthComponent : public Node2D {
	GDCLASS(HealthComponent, Node2D)

protected:
	static void _bind_methods();

private:
    double max_hp;
    double hp;

public:
	HealthComponent();
	~HealthComponent();

	void _ready() override;
    void _process(double delta) override;

    void damage(double damage);
    void heal(double hill);

    void set_max_hp(const double p_max_hp);
    double get_max_hp() const;

};

}	// namespace godot

#endif // HEALTH_COMPONENT_H