#include "collider.h"

#include <iostream>

#include "engine.h"

void Collider::check_intersect_window() {
  auto shape = get_shape();
  auto screen_size = engine::get_screen_size();

  if (shape.left + shape.width > screen_size.x) {
    notify_intersect_window(RIGHT);
  }

  if (shape.left < 0) {
    notify_intersect_window(LEFT);
  }

  if (shape.top + shape.height > screen_size.y) {
    notify_intersect_window(BOTTOM);
  }

  if (shape.top < 0) {
    notify_intersect_window(TOP);
  }
}