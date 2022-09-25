#include "engine.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace engine {
Engine global;

sf::Vector2u get_screen_size() { return global.get_screen_size(); }

void Engine::run() {
  fps_clock.restart();

  start();

  while (window.isOpen()) {
    sf::Clock frame_clock;

    process_events();

    auto delta_time = fps_clock.restart();

    update(delta_time);

    clear_screen();
    draw();

    check_collisions();
    // Framerate calc
    auto elapsed = frame_clock.getElapsedTime().asMilliseconds();
    auto sleep_time = 1000.0 / fps - elapsed;
    sf::sleep(sf::milliseconds(sleep_time));
  }
}

void Engine::stop() { window.close(); }

void Engine::process_events() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      stop();
    }

    if (event.type == sf::Event::KeyPressed) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        stop();
      }
    }
  }
}

void Engine::clear_screen() {
  for (auto& obj : game_objects) {
    auto drawable = obj->get_drawable();

    if (drawable) {
      
      const auto sprite_offset = 30;
      
      auto rect = drawable->get_global_bounds();

      auto size = rect.getSize();
      size.x += sprite_offset;
      size.y += sprite_offset;

      auto pos = rect.getPosition();
      pos.x -= sprite_offset / 2.0;
      pos.y -= sprite_offset / 2.0;

      sf::RectangleShape rectangle(size);
      rectangle.setPosition(pos);
      rectangle.setFillColor(background_color);
      window.draw(rectangle);
    }
  }
}

void Engine::draw() {
  for (const auto& obj : game_objects) {
    auto drawable = obj->get_drawable();
    if (drawable) {
      drawable->draw(window);
    }
  }

  window.display();
}

sf::Vector2u Engine::get_screen_size() { return window.getSize(); }

void Engine::check_collisions() {
  for (size_t i = 0; i < game_objects.size(); i++) {
    auto collider = game_objects[i]->get_collider();

    if (collider == nullptr) continue;

    for (size_t j = i + 1; j < game_objects.size(); j++) {
      auto other_collider = game_objects[j]->get_collider();

      if (other_collider == nullptr) continue;

      collider->check_intersect(*other_collider);
    }

    collider->check_intersect_window();
  }
}

void Engine::set_window_settings(sf::VideoMode mode, const sf::String& title,
                                 sf::Uint32 style) {
  window.create(mode, title, style);
}

void Engine::set_fps(double fps) { this->fps = fps; }

void Engine::add_object(std::shared_ptr<Object> object) {
  game_objects.push_back(std::move(object));
}

void Engine::start() {
  for (auto& obj : game_objects) {
    obj->start();
  }
}

void Engine::update(const Time& delta_time) {
  for (auto& obj : game_objects) {
    obj->update(delta_time);
    obj->process_components();
  }
}

}  // namespace engine