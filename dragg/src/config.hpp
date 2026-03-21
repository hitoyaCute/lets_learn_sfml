#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>
namespace conf {
  const sf::Vector2u win_size = {1280, 800};
  const auto win_size_f = static_cast<sf::Vector2f>(win_size);

  const uint32_t max_framerate = 60;
};


