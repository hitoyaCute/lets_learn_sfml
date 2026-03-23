#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"
#include "Interpolated/Interpolated.hpp"

#include <array>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

void setup_numpad(std::array<ButtonState,19>& buttons) {
    // array struct
    //     037 141 245 349
    // 103 Del  C   %   +
    // 174  7   8   9   -
    // 245  4   5   6   *
    // 316  1   2   3   /
    // 387  0   .   [ = ]
    
             // row 103
    buttons[0].pos = { 37, 103}; buttons[0].name = "Del";
    buttons[1].pos = {141, 103}; buttons[1].name = "C";
    buttons[2].pos = {245, 103}; buttons[2].name = "%"; 
    buttons[3].pos = {349, 103}; buttons[3].name = "+"; 
    // row 174
    buttons[4].pos = { 37, 174}; buttons[4].name = "7"; 
    buttons[5].pos = {141, 174}; buttons[5].name = "8"; 
    buttons[6].pos = {245, 174}; buttons[6].name = "9"; 
    buttons[7].pos = {349, 174}; buttons[7].name = "-"; 
    // row 245 [0].pos = 
    buttons[8].pos  = { 37, 245}; buttons[8].name = "4"; 
    buttons[9].pos  = {141, 245}; buttons[9].name = "5"; 
    buttons[10].pos = {245, 245}; buttons[10].name = "6"; 
    buttons[11].pos = {349, 245}; buttons[11].name = "*"; 
    // row 316 [0].pos = 
    buttons[12].pos = { 37, 316}; buttons[12].name = "1"; 
    buttons[13].pos = {141, 316}; buttons[13].name = "2"; 
    buttons[14].pos = {245, 316}; buttons[14].name = "3"; 
    buttons[15].pos = {349, 316}; buttons[15].name = "/"; 
    // row 387 [0].pos = 
    buttons[16].pos = { 37, 387}; buttons[16].name = "0"; 
    buttons[17].pos = {141, 387}; buttons[17].name = "."; 
    buttons[18].pos = {245, 387}; buttons[18].size = {198, 60}; buttons[18].name = "=";
}

class Color : public sf::Color {
public:
    constexpr Color(const sf::Color& col): sf::Color{col}{};
    constexpr Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 255): sf::Color{r,g,b,a}{}

    constexpr Color operator*(const float d) const {
        constexpr auto scaledMul = [](const std::uint8_t lhs, const float rhs) {
            const auto uint16Result = static_cast<std::uint16_t>(lhs * rhs);
            return static_cast<std::uint8_t>(uint16Result / 255u);
        };

        return Color{scaledMul(this->r, d), scaledMul(this->g, d), scaledMul(this->b, d), this->a};
    }
    constexpr void operator*=(const float d) {
        constexpr auto scaledMul = [](const std::uint8_t lhs, const float rhs) {
            const auto uint16Result = static_cast<std::uint16_t>(lhs * rhs);
            return static_cast<std::uint8_t>(uint16Result / 255u);
        };
        r = scaledMul(this->r, d);
        g = scaledMul(this->g, d);
        b = scaledMul(this->b, d);
    }
};


void draw_numpad(sf::RenderTarget& win, const std::array<ButtonState,19>& buttons) {
    const ulong vect_count = 8 * 4;
    
    const float border_thickness = 0.9;
    const float r = 23.f;

    sf::VertexArray button_vertex{sf::PrimitiveType::TriangleFan, vect_count};

    sf::Text t{conf::button_font};
    t.setStyle(sf::Text::Style::Bold);
    t.setCharacterSize(20);
    t.setFillColor(conf::button_fg);


    for (const auto& button: buttons) {
        Color border_col {255,255,255};
        Color button_bg = conf::button_bg;

        // change colors for highlighting
        const float scale = (float)button.border_scale / 255.f; // fetch and mutate the scalar
        button_bg -= Color{50,50,50,0} * (255*(float)button.is_click); // same here
        border_col += border_col * scale;
        // we use easing function on a linear easing function to allow a more
        // fun interpolation
        const float final_border_thickness = 
            Interpolation::EasingFunc::easeOutElastic(scale) * border_thickness * 2 + border_thickness;

        // draw the border
        Calc::Shape::CreateRoundedRect(button_vertex, vect_count, r + border_thickness,
                sf::Vector2f{button.size.x + final_border_thickness * 2,
                             button.size.y + final_border_thickness * 2},
                sf::Vector2f{button.pos.x - final_border_thickness,
                             button.pos.y - final_border_thickness},
                border_col);
        win.draw(button_vertex);

        // draw the button bg
        Calc::Shape::CreateRoundedRect(button_vertex, vect_count, r, button.size, button.pos, button_bg);
        win.draw(button_vertex);

        // prepare the text, and make sure its centered
        t.setString(button.name);
        t.setPosition(sf::Vector2f{button.pos.x, button.pos.y - 3} + (.5f * button.size));
        t.setOrigin(t.getLocalBounds().size / 2.f);
        
        win.draw(t);
    }
}

