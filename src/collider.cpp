#include "collider.h"

#include <iostream>

#include "engine.h"

const float eps = 0.9;

void Collider::check_intersect_window() {
  auto shape = get_shape();
  auto screen_size = engine::get_screen_size();

  if (screen_size.x - (shape.left + shape.width) <= eps) {
    notify_intersect_window(RIGHT);
  }

  if (shape.left <= 0) {
    notify_intersect_window(LEFT);
  }

  if (screen_size.y - (shape.top + shape.height) <= eps) {
    notify_intersect_window(BOTTOM);
  }

  if (shape.top <= 0) {
    notify_intersect_window(TOP);
  }
}