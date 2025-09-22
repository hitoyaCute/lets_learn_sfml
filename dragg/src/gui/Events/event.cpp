#include "events.hpp"
#include <SFML/Window/Keyboard.hpp>

bool vals::is_entered = false;

void process_event(sf::Window& window){
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (key->scancode == sf::Keyboard::Scancode::Escape){
        window.close();
      }
      if (key->scancode == sf::Keyboard::Scancode::Enter){
        vals::is_entered = !vals::is_entered;
      }
    }
  }
}
