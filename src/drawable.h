#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SFML/Graphics/RenderTarget.hpp>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "component.h"

class Drawable {
 public:
  virtual ~Drawable() = default;
  virtual void draw(sf::RenderTarget& render) = 0;
  virtual sf::FloatRect get_global_bounds() const = 0;
};

#endif  // __DRAWABLE_H__