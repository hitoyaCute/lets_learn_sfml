#include "events.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>
#include "config.hpp"
#include "star.hpp"


// create a stars on random positions and random depth
std::vector<Star> createStars(uint32_t count, float scale = 1.f) {

  std::vector<Star> stars;
  stars.reserve(count);
  
  // random number gen
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.f, 1.f);

  // define star free zone
  const sf::Vector2f window_world_size = conf::win_size_f * conf::near;
  const sf::FloatRect star_free_zone = {-window_world_size * 0.5f, window_world_size};

  // creating the stars
  for (uint32_t i{count}; i--;) {
    const float x = (dis(gen) - 0.5f) * conf::win_size_f.x * scale;
    const float y = (dis(gen) - 0.5f) * conf::win_size_f.y * scale;
    const float depth = dis(gen) * (conf::far - conf::near) + conf::near;
  
    // relocate any star inside the star free zone
    if (star_free_zone.contains({x,y})) {
      i++;
      continue;
    }
    stars.push_back({{x, y}, depth});
  }
  
  // depth sorting
  std::sort(stars.begin(), stars.end(), [](const Star& s_1, const Star& s_2) {
    return s_1.depth > s_2.depth;
  });

  return stars;
}



void updateGeometry(uint32_t idx, const Star& s, sf::VertexArray& va) {
  const float scale = 1.f / s.depth;

  const float depth_ratio = (s.depth - conf::near) / (conf::far - conf::near);
  const float color_ratio = 1.f - depth_ratio;

  const auto c = static_cast<uint8_t>(color_ratio * 255.f);
  
  const sf::Vector2f p = s.position * scale;
  const float r = conf::star_radius * scale;
  const uint32_t i = 6 * idx;

  // top triangle
  va[i + 0].position = {p.x - r, p.y - r};
  va[i + 1].position = {p.x + r, p.y - r};
  va[i + 2].position = {p.x + r, p.y + r};

  // bottom triangle
  // va[i + 3].position = va[i + 0].position;
  va[i + 4].position = {p.x - r, p.y + r};
  // va[i + 5].position = va[i + 2].position;

  // setting colors
  const sf::Color color{c,c,c};
  va[i + 0].color = color;
  va[i + 1].color = color;
  va[i + 2].color = color;
  va[i + 3] = va[i + 0];
  va[i + 4].color = color;
  va[i + 5] = va[i + 2];
}





int main (int argc, char *argv[]) {
  sf::RenderWindow window{sf::VideoMode{conf::win_size}, "Stars", sf::State::Fullscreen};
  window.setFramerateLimit(conf::max_framerate);
  window.setMouseCursorVisible(false);

  sf::Texture star_texture("../res/star.png");
  star_texture.setSmooth(true);
  const auto a = star_texture.generateMipmap();
  

  std::vector<Star> stars = createStars(conf::count, conf::far);
  sf::VertexArray va{sf::PrimitiveType::Triangles, 6 * conf::count};

  const auto texture_size_f = static_cast<sf::Vector2f>(star_texture.getSize());
  for (uint32_t idx{conf::count}; idx--;) {
    const uint32_t i = 6 * idx;
    // top traingle
    va[i + 0].texCoords = {0.f, 0.f};
    va[i + 1].texCoords = {texture_size_f.x, 0.f};
    va[i + 2].texCoords = {texture_size_f.x, texture_size_f.y};

    // bottom triangle
    // va[i + 3] = va[i + 0];
    va[i + 4].texCoords = {0.f, texture_size_f.y};
    // va[i + 5] = va[i + 2];
  }

  uint32_t first = 0;
  while (window.isOpen()) {
    process_event(window);
    window.clear();
    
    for (uint32_t i{conf::count}; i--;) {
      Star& s = stars[i];
      s.depth -= conf::speed * conf::dt;
      if (s.depth < conf::near) {
        //
        s.depth = conf::far - (conf::near - s.depth);
        //
        first = i;
      }
    }

    for (uint32_t i{0}; i < conf::count; i++) {
      const uint32_t idx = (i + first) % conf::count;
      const Star& s = stars[idx];
      
      updateGeometry(i, s, va);
    }

    sf::RenderStates states;
    states.transform.translate(conf::win_size_f * 0.5f);
    states.texture = &star_texture;
    window.draw(va, states);

    window.display();
  }

  return 0;
}

