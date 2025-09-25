#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

namespace MEU {

struct Drawable {
  sf::VertexArray object;
  std::unique_ptr<sf::VertexArray> objBound;
  const size_t size;
  sf::Color id;
  sf::Vector2f position;
  void setPosition(sf::Vector2f pos);
  void setFillColor(sf::Color col);
  Drawable(const sf::VertexArray& arr, size_t size_, sf::Color id_, sf::Vector2f pos);
  Drawable(const sf::VertexArray& arr, size_t size_, sf::Vector2f pos);

  ~Drawable() = default;

  // std::function<void(Drawable self, const UserState& button)>* interact;
};


}; // namespace MEU
