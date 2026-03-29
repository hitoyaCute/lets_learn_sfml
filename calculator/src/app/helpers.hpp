#pragma once

#include "Interpolated/Interpolated.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstdint>
#include <string>


struct ButtonState {
    sf::Vector2f pos = {0,0};
    sf::Vector2f size = {94, 60};
    std::string name = "";
    // the transition animation value
    // where 0 is the default, 255 is the max transition value
    Interpolation::Interpolated<uint8_t> border_scale {0, 0.8f};
    // scale that defines how much is the change
    // 0 is no change, 255 is the max change
    Interpolation::Interpolated<uint8_t> color_scale {0, 0.4f};
    // if its key is being hold
    bool is_key_pressed = false;
    // if the mouse is abouve the button
    bool is_hover = false;
    // if being hold using mouse
    bool is_click = false;
};

void setup_numpad(std::array<ButtonState,19>& buttons);
void draw_numpad(sf::RenderTarget& win, const std::array<ButtonState,19>& buttons);
void draw_numdisplay(sf::RenderTarget& win, const std::string d);

inline void setFillColor(sf::VertexArray& arr, const sf::Color& col) {
    for (size_t i = 0; i < arr.getVertexCount(); ++i) {
        arr[i].color = col;
    }
}
