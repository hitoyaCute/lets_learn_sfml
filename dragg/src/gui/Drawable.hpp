#pragma once
#include <SFML/Graphics/VertexArray.hpp>

namespace MEU {

struct Drawable {
  sf::VertexArray* object;
  sf::VertexArray* objBound;
  const size_t size;
  sf::Color id;
  sf::Vector2f position;
  void setPosition(sf::Vector2f pos);
  void setFillColor(sf::Color col);
  Drawable(sf::VertexArray& arr, size_t size_, sf::Color id_, sf::Vector2f pos);
  Drawable(sf::VertexArray& arr, size_t size_, sf::Vector2f pos);

  // std::function<void(Drawable self, const UserState& button)>* interact;
};


}; // namespace MEU
