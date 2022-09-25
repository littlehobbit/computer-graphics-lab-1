#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "component.h"
#include "object.h"

class Drawable;

namespace engine {

template <typename ObjectType, typename... Args>
inline ObjectType* create_object(Args&&... args);

sf::Vector2u get_screen_size();

class Engine {
 public:
  void run();
  void stop();

  void set_window_settings(sf::VideoMode mode, const sf::String& title,
                           sf::Uint32 style = sf::Style::Default);
  void set_fps(double fps);

  void add_object(std::shared_ptr<Object> object);

  sf::Vector2u get_screen_size();

 private:
    void check_collisions();
  void start();
  void update(const Time& delta_time);
  //   void fixed_update(const Time &delta_time);
  void process_events();
  void clear_screen();
  void draw();

  std::vector<std::shared_ptr<Object>> game_objects;

  sf::Color background_color = sf::Color::Black;
  sf::RenderWindow window{sf::VideoMode(800, 600), "title"};
  double fps = 60;
  sf::Clock fps_clock;
};

extern Engine global;

template <typename ObjectType, typename... Args>
ObjectType* create_object(Args&&... args) {
  auto object = std::make_shared<ObjectType>(args...);
  global.add_object(object);
  return object.get();
}

}  // namespace engine

#endif  // __ENGINE_H__