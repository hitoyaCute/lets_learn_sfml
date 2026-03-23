#pragma once

#include "app/helpers.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

void process_event(sf::RenderWindow& win, std::vector<ButtonState>& buttons);
