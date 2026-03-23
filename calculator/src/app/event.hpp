#pragma once

#include "app/helpers.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <string>

void process_event(sf::RenderWindow& win, std::map<std::string, ButtonState>& buttons);
