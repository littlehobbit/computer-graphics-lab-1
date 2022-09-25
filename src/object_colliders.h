#ifndef __OBJECT_COLLIDERS_H__
#define __OBJECT_COLLIDERS_H__

#include <SFML/Graphics/RectangleShape.hpp>

#include "collider.h"
#include "engine.h"
#include "object.h"

class BoxCollider : public Collider {
 public:
  BoxCollider(Object* owner, float size) : Collider(owner), box({size, size}) {
    box.setOrigin(size / 2, size / 2);
  }

  void process() override {
    box.setPosition(owner->transform.position);
  }

  sf::FloatRect get_shape() const override { return box.getGlobalBounds(); }

 private:
  sf::RectangleShape box;
};

#endif  // __OBJECT_COLLIDERS_H__