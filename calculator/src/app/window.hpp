#pragma once

// this will contain the thing to be processed on the window
#include "ui/Graphics/RerderWindow.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

namespace Calc {
namespace Window {


void process_event(sf::Window& window, Graphics::RenderWindow& manager);

};// namespace Window
};// namespace Calc

