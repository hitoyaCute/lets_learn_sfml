#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>
namespace conf {
  const sf::Vector2u win_size = {1280,800};
  const sf::Vector2f win_size_f = static_cast<sf::Vector2f>(win_size);
  
  const uint32_t max_framerate = 60u;
  const float dt = 1.f / (float)max_framerate;
  
  const uint32_t count = 300;
  const float star_radius = 40.f;
  
  const float far = 10.f;
  const float near = 0.1f;
  const float speed = 1.f;

};



