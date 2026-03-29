#pragma once

#include "app/helpers.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

struct event{
    std::string name;
    bool is_pressed;
};


void process_event(sf::RenderWindow& win);
// process button events and call a specific function to resolve that event
void update_buttons(sf::RenderWindow& win, std::array<ButtonState, 19>& buttons, void (*handle_event)(event event_info) = 0);
