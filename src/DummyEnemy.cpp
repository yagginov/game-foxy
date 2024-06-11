#include "DummyEnemy.h"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

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
    animatedSprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
}

void DummyEnemy::_process(double delta) {
    // Оновлюємо текст ярлика здоров'я
    if (health_label) {
        health_label->set_text(String::num(hp));
    }
    if (!animatedSprite->is_playing())
    {
        animatedSprite->play("idle");
    }
}

void DummyEnemy::take_damage(int amount) {
    // Логіка обробки пошкодження
    hp -= amount;
    if (hp <= 0) {
        hp = 0;
        // Логіка смерті або інші дії
    }
    animatedSprite->play("take_damage");
}
