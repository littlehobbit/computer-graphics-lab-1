#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <vector>

#include "SFML/System/Vector2.hpp"
#include "collider.h"
#include "component.h"
#include "drawable.h"
#include "utils.h"

struct Transform {
  sf::Vector2f position = {0, 0};
  double rotation = 0;
};

class Object {
 public:
  virtual ~Object() = default;

  virtual void start(){};

  virtual void update(const Time& time){};

  void process_components() {
    for (auto& comp : components) {
      comp->process();
    }
  }

  template <typename ComponentType>
  ComponentType* get_component() const;

  template <typename ComponentType, typename... Args>
  ComponentType* create_component(Args&&... args);

  Drawable* get_drawable() { return drawable.get(); }

  Collider* get_collider() { return collider.get(); }

  Transform transform;

 private:
  std::shared_ptr<Drawable> drawable;
  std::shared_ptr<Collider> collider;
  std::vector<std::shared_ptr<Component>> components;
};

template <typename ComponentType>
ComponentType* Object::get_component() const {
  for (auto& component : components) {
    auto cast = dynamic_cast<ComponentType*>(component.get());
    if (cast != nullptr) {
      return cast;
    }
  }

  return nullptr;
}

template <typename ComponentType, typename... Args>
ComponentType* Object::create_component(Args&&... args) {
  auto component = std::make_shared<ComponentType>(this, args...);

  if (dynamic_cast<Drawable*>(component.get()) != nullptr) {
    drawable = std::dynamic_pointer_cast<Drawable>(component);
  }

  if (dynamic_cast<Collider*>(component.get()) != nullptr) {
    collider = std::dynamic_pointer_cast<Collider>(component);
  }

  components.push_back(component);
  return component.get();
}

#endif  // __OBJECT_H__