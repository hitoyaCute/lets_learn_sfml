#pragma once

#include "Interpolated/Interpolated.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <string>


struct ButtonState {
    sf::Vector2f pos;
    sf::Vector2f size = {94, 60};
    std::string name = "";
    // the transition animation value
    // where 0 is the default, 255 is the max transition value
    Interpolation::Interpolated<uint8_t> border_scale {0, 0.6f};
    // scale that defines how much is the change
    // 0 is no change, 255 is the max change
    Interpolation::Interpolated<uint8_t> color_scale {0, 0.4f};
    bool is_hover = false;
    bool is_click = false;
    ButtonState(const sf::Vector2f& p, const char* n): pos{p}, name{n}{}
    ButtonState(const sf::Vector2f& p, const sf::Vector2f s, const char* n):pos{p},size{s},name{n}{}
};

void setup_numpad(std::vector<ButtonState>& buttons);
void draw_numpad(sf::RenderTarget& win, const std::vector<ButtonState>& buttons);
void draw_numdisplay(sf::RenderTarget& win, const std::string& d);


