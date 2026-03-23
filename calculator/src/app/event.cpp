#include "event.hpp"
#include "app/helpers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <string>

std::string get_name_button_at(const sf::Vector2f& pos, const std::map<std::string, ButtonState>& buttons) {
    for (const auto& button: buttons){
        if (sf::Rect<float>{button.second.pos, button.second.size}.contains(pos)) {
            return button.first;
        }
    }
    return "";
}

void process_event(sf::RenderWindow &win, std::map<std::string, ButtonState>& buttons) {
    // process events
    auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        }
        else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                win.close();
            }
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            std::string button = get_name_button_at(mouse_pos, buttons);
            if (!button.empty() and mouse->button == sf::Mouse::Button::Left) {
                buttons[button].is_click = true;
                buttons[button].color_scale = -1;
            }
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
            std::string button = get_name_button_at(mouse_pos, buttons);
            if (!button.empty() and mouse->button == sf::Mouse::Button::Left) {
                buttons[button].is_click = false;
                buttons[button].color_scale = 0;
            }
        }
    }

    // restore all if needed
    for (auto& i: buttons) {
        auto& button = buttons[i.first];
        const bool inside = sf::FloatRect{button.pos, button.size}.contains(mouse_pos);
        if(!inside and button.is_hover) {
            button.is_hover = false;
            button.border_scale = 0;
        }
        else if(inside and !button.is_hover) {
            button.is_hover = true;
            button.border_scale = -1;
        }
    }
}


