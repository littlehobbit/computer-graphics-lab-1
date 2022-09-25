#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include <functional>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "component.h"

enum WindowPart { TOP, BOTTOM, LEFT, RIGHT };

class Collider : public Component {
 public:
  using OnIntersect = std::function<void()>;
  using OnIntersectWindow = std::function<void(WindowPart)>;

  Collider(Object* owner) : Component(owner) {}

  void set_on_intersect(OnIntersect on_intersect) {
    this->on_intersect = std::move(on_intersect);
  }

  void set_on_intersect_window(OnIntersectWindow on_intersect_window) {
    this->on_intersect_window = std::move(on_intersect_window);
  }

  virtual void check_intersect(Collider& other) {
    if (this->get_shape().intersects(other.get_shape())) {
      notify_intersect();
      other.notify_intersect();
    }
  }

  void check_intersect_window();

 protected:
  virtual sf::FloatRect get_shape() const = 0;

  void notify_intersect_window(WindowPart part) {
    if (on_intersect_window) on_intersect_window(part);
  }

  void notify_intersect() {
    if (on_intersect) on_intersect();
  }

 private:
  OnIntersect on_intersect;
  OnIntersectWindow on_intersect_window;
};

#endif  // __COLLIDER_H__