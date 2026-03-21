#include <cstdio>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "window.hpp"
#include "ui/Graphics/states.hpp"
#include "ui/Graphics/RerderWindow.hpp"
#include "ui/Graphics/Interactable.hpp"
#include "util/time.hpp"

// this will contain the thing to be processed on the window
namespace Calc {
namespace Window {

Interaction_state d{};

void process_event(sf::Window& window, Graphics::RenderWindow& manager){

    // take the object bellow the screen from previous
    Graphics::InteractableElement* picked = 0;
    picked = manager.get_elem_under(d.mouse_position_value);

    d.event = Interaction_state::event_type::hovering;
    d.mouse_position_value = sf::Mouse::getPosition(window);

    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape){
                window.close();
            }
        }
        // process mouse event
        else if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>()) {
            d.mouse_event_value = m->button;
            d.time_since_ldown = Time.time();
            
            d.mouse_position_value = m->position;
            picked = manager.get_elem_under(m->position);

            switch (m->button) {
                case sf::Mouse::Button::Left:
                    d.event = Interaction_state::event_type::left_down;
                    break;
                case sf::Mouse::Button::Right:
                    d.event = Interaction_state::event_type::right_down;
                    break;
                default:break;
            }
        } else if (const auto* m = event->getIf<sf::Event::MouseButtonReleased>()) {
            d.mouse_event_value = m->button;
            d.time_since_ldown = Time.time();

            switch (m->button) {
                case sf::Mouse::Button::Left:
                    d.event = Interaction_state::event_type::left_up;
                    break;
                case sf::Mouse::Button::Right:
                    d.event = Interaction_state::event_type::right_up;
                    break;
                default:
                    break;
            }
        } else {
            
        }

        if (!event->is<sf::Event::MouseButtonPressed>() or
            !event->is<sf::Event::MouseButtonReleased>()) {
            // handle hovering
            
        }
        
        // call the object for each events
        if (picked)
            picked->callback(d);
    }
}


};// namespace Window

};// namespace Calc

