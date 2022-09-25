#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "component.h"
#include "drawable.h"
#include "object.h"

class Sprite : public Component, public Drawable {
 public:
  Sprite(Object* owner) : Component(owner) {}

  virtual void set_color(sf::Color color) = 0;
};

template <typename Shape>
class SpriteShape : public Sprite {
 public:
  template <typename... ShapeArgs>
  SpriteShape(Object* owner, const std::string& texture_path,
              ShapeArgs&&... args)
      : Sprite(owner), shape(args...) {
    texture.loadFromFile(texture_path);
    shape.setTexture(&texture);
    auto bound = shape.getLocalBounds();
    shape.setOrigin(bound.width / 2, bound.height / 2);
  }

  void draw(sf::RenderTarget& render) override { render.draw(shape); }

  sf::FloatRect get_global_bounds() const override {
    return shape.getGlobalBounds();
  }

  void set_color(sf::Color color) override { shape.setFillColor(color); }

  void process() override {
    shape.setPosition(owner->transform.position);
    shape.setRotation(owner->transform.rotation);
  }

 private:
  sf::Texture texture;
  Shape shape;
};

template <typename Shape>
class SimpleShape : public Sprite {
 public:
  template <typename... ShapeArgs>
  SimpleShape(Object* owner, sf::Color color, ShapeArgs&&... args)
      : Sprite(owner), shape(args...) {
    shape.setFillColor(color);
    auto bound = shape.getLocalBounds();
    shape.setOrigin(bound.width / 2, bound.height / 2);
  }

  sf::FloatRect get_global_bounds() const override {
    return shape.getGlobalBounds();
  }

  void set_color(sf::Color color) override { shape.setFillColor(color); }

  void draw(sf::RenderTarget& render) override { render.draw(shape); }

  void process() override {
    shape.setPosition(owner->transform.position);
    shape.setRotation(owner->transform.rotation);
  }

 private:
  Shape shape;
};

#endif  // __SPRITE_H__