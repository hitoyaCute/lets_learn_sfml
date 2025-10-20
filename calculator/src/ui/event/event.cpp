#include "events.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <optional>

namespace Calc {

void process_event(sf::Window& window){
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape){
        window.close();
      }
    }
  }
}

}; // namespace Calc

