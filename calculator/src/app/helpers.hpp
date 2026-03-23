#pragma once

#include "Interpolated/Interpolated.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <map>
#include <string>


struct ButtonState {
    sf::Vector2f pos;
    sf::Vector2f size = {94, 60};
    // the transition animation value
    // where 0 is the default, 255 is the max transition value
    Interpolation::Interpolated<uint8_t> border_scale {0, 0.4f};
    // scale that defines how much is the change
    // 0 is no change, 255 is the max change
    Interpolation::Interpolated<uint8_t> color_scale {0, 0.4f};
    bool is_hover = false;
    bool is_click = false;
};

void setup_numpad(std::map<std::string,ButtonState>& buttons);
void draw_numpad(sf::RenderTarget& win, const std::map<std::string,ButtonState> buttons);
void draw_numdisplay(sf::RenderTarget& win, const std::string& d);


