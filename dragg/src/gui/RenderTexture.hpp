#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "RenderManager.hpp"

namespace MEU {

class viewPort {
  Renderer<sf::RenderTexture> target;
  // position relative to the parent holder
  sf::Vector2f pos;
  sf::View view;
};

}; // namespace MEU
