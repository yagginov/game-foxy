#include "DummyEnemy.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

void DummyEnemy::_bind_methods() {
    ClassDB::bind_method(D_METHOD("take_damage", "amount"), &DummyEnemy::take_damage);
}

DummyEnemy::DummyEnemy() {
    hp = 100; // базове значення здоров'я (можна налаштувати як завгодно)
}

DummyEnemy::~DummyEnemy() {
}

void DummyEnemy::_ready() {
    // Використовуємо шаблонний метод get_node для отримання вузла з явним вказанням типу
    health_label = get_node<Label>("HealthLabel");
    set_physics_process(true);

    // Додаємо до групи "enemies"
    add_to_group("enemies");
}

void DummyEnemy::_process(double delta) {
    // Оновлюємо текст ярлика здоров'я
    if (health_label) {
        health_label->set_text(String::num(hp));
    }
}

void DummyEnemy::take_damage(int amount) {
    // Логіка обробки пошкодження
    hp -= amount;
    if (hp <= 0) {
        hp = 0;
        // Логіка смерті або інші дії
    }
}
