#include "event.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdio>


void process_event(sf::RenderWindow &win) {
    // process events
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        }
        else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                win.close();
            }
        }
    }
}

