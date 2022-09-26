// #include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

// #include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "component.h"
#include "drawable_components.h"
#include "engine.h"
#include "object.h"
#include "object_colliders.h"

class MovableObject : public Object {
 public:
  MovableObject(sf::Vector2f speed, float rotate_speed)
      : Object(), speed(speed), rotation_speed(rotate_speed) {}

  void start() override {
    auto sprite = get_component<Sprite>();

    auto collider = this->get_component<Collider>();
    collider->set_on_intersect_window([this, sprite](WindowPart part) {
      sf::Color random(rand(), rand(), rand());
      sprite->set_color(random);

      switch (part) {
        case TOP:
        case BOTTOM:
          speed.y *= -1;
          break;

        case LEFT:
        case RIGHT:
          speed.x *= -1;
          break;
      }
    });
  }

  void update(const Time& delta) override {
    this->delta = delta;
    this->transform.position += speed * delta.asSeconds();
    this->transform.rotation += rotation_speed * delta.asSeconds();
  }

 private:
  sf::Vector2f speed;
  float rotation_speed;
  Time delta{};
};

int main(int argc, char* argv[]) {
  auto& engine = engine::global;
  engine.set_window_settings(sf::VideoMode::getDesktopMode(), "lab-1",
                             sf::Style::Fullscreen);
  engine.set_fps(60);

  srand(time(0));
  for (size_t i = 0; i < 200; i++) {
    sf::Vector2f speed(rand() % 300 + 50.0, rand() % 300 + 50.0);

    double rotation_speed = rand() % 100;

    auto obj = engine::create_object<MovableObject>(speed, rotation_speed);

    auto shape = rand() % 3;
    if (shape == 0) {
      obj->create_component<SimpleShape<sf::RectangleShape>>(
          sf::Color::Blue, sf::Vector2f{70, 70});
      obj->create_component<BoxCollider>(70);
    } else if (shape == 1) {
      auto random_radius = rand() % 110 + 10;
      obj->create_component<SimpleShape<sf::CircleShape>>(sf::Color::Red,
                                                          random_radius);
      obj->create_component<BoxCollider>(random_radius * 2);
    } else {
      if (rand() % 2) {
        obj->create_component<SpriteShape<sf::CircleShape>>(
            "resources/image.bmp", 100);
        obj->create_component<BoxCollider>(200);
        obj->transform.position = {200, 200};
      } else {
        obj->create_component<SimpleShape<sf::RectangleShape>>(
            sf::Color::Green, sf::Vector2f{70, 70});
        obj->create_component<BoxCollider>(70);
      }
    }

    auto screen_size = engine::get_screen_size();
    obj->transform.position =
        sf::Vector2f(screen_size.x / 2.0, screen_size.y / 2.0);
  }

  engine.run();
}