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
#include <SFML/System/Vector3.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>
#include "config.hpp"
#include "Interpolated.hpp"

int main (int argc, char *argv[]) {
  sf::RenderWindow window{sf::VideoMode{conf::win_size}, "Interpolated", sf::State::Fullscreen};
  window.setFramerateLimit(conf::max_framerate);
  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);

  
  Interpolation::Interpolated<sf::Vector2f> a_pos{};
  // sf::Vector2f a_pos{50.0f,50.0f};
  
  a_pos.setDuration(1.f);
  a_pos.transition = Interpolation::Easing::easeOutElastic;

  Interpolation::Interpolated<sf::Vector3f>a_color{{0,0,50}};
  a_color.transition = Interpolation::Easing::linear;
  a_color.setDuration(2.f);

  bool is_changed = false;
  while (window.isOpen()) {
    process_event(window);
    // clear the screen with black{dont tell cops}
    window.clear();



    if (vals::is_entered and !is_changed){
      constexpr sf::Vector2f new_pos{800.f,600.f};
      a_pos = new_pos;
      a_color = sf::Vector3f{255,0,0};
      std::cout << "meh" << std::endl;
      
      is_changed = true;
    }

    // create a circle shape
    sf::CircleShape a{100}; // wtf??
    // just a setter for the color type
    auto pree_col = sf::Vector3f{a_color};
    auto col = static_cast<sf::Vector3<unsigned char>>(pree_col);
    a.setFillColor(sf::Color{col.x,col.y,col.z});
    // set the circle's position
    a.setPosition(a_pos);



    // draw the circle
    window.draw(a);
    // flush to the display
    window.display();
  }

  return 0;
}

