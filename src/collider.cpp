#include "collider.h"

#include <iostream>

#include "engine.h"

void Collider::check_intersect_window() {
  auto shape = get_shape();
  auto screen_size = engine::get_screen_size();

  if (shape.getPosition().x + shape.width > screen_size.x) {
    notify_intersect_window(RIGHT);
  }

  if (shape.getPosition().x < 0) {
    notify_intersect_window(LEFT);
  }

  if (shape.getPosition().y + shape.height > screen_size.y) {
    notify_intersect_window(BOTTOM);
  }

  if (shape.getPosition().y < 0) {
    notify_intersect_window(TOP);
  }
}