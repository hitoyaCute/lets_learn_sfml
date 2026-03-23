#pragma once

#include "app/helpers.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

void process_event(sf::RenderWindow& win, std::array<ButtonState, 19>& buttons);
