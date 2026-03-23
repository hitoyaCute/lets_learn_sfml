#include "event.hpp"
#include "Interpolated/Interpolated.hpp"
#include "app/helpers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <vector>

ButtonState* get_button_at(const sf::Vector2f& pos, std::vector<ButtonState>& buttons) {
    for (size_t i =0; i < buttons.size(); i++){
        if (sf::Rect<float>{buttons[i].pos, buttons[i].size}.contains(pos)) {
            return &buttons[i];
        }
    }
    return 0;
}

void process_event(sf::RenderWindow &win, std::vector<ButtonState>& buttons) {
    // process events
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            win.close();
        }
        else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Escape) {
                win.close();
            }
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
            ButtonState* button = get_button_at(mouse_pos, buttons);
            if (button and mouse->button == sf::Mouse::Button::Left) {
                printf("pressed\n");
                button->is_click = true;
                button->color_scale.setDuration(0.4);
                button->color_scale = -1;
            }
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
            auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
            ButtonState* button = get_button_at(mouse_pos, buttons);
            if (button and mouse->button == sf::Mouse::Button::Left) {
                printf("released\n");
                button->is_click = false;
                button->color_scale.setDuration(0.01);
                button->color_scale = 0;
            }
        }
    }

    auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
    // restore all if needed
    for (auto& button: buttons) {
        const bool inside = sf::FloatRect{button.pos, button.size}.contains(mouse_pos);
        if(not inside and button.is_hover) {
            button.is_hover = false;
            button.border_scale.setDuration(0.01);
            button.color_scale.setDuration(0.01);
            button.color_scale  = 0;
            button.border_scale = 0;
        }
        else if(inside and not button.is_hover) {
            button.is_hover = true;
            button.border_scale.setDuration(0.6);
            button.border_scale = -1;
        }
    }
}


