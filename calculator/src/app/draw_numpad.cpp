#include "Interpolated/Interpolated.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"

#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

void setup_numpad(std::map<std::string, ButtonState>& buttons) {
    // array struct
    //     037 141 245 349
    // 103 Del  C   %   +
    // 174  7   8   9   -
    // 245  4   5   6   *
    // 316  1   2   3   /
    // 387  0   .   [ = ]
    
             // row 103                          
    buttons["Del"] =ButtonState{{37,  103}};
    buttons["C"] = ButtonState{{141, 103}}; 
    buttons["%"] = ButtonState{{245, 103}}; 
    buttons["+"] = ButtonState{{349, 103}}; 
    // row 174
    buttons["7"] = ButtonState{{37,  174}}; 
    buttons["8"] = ButtonState{{141, 174}}; 
    buttons["9"] = ButtonState{{245, 174}}; 
    buttons["-"] = ButtonState{{349, 174}}; 
    // row 245 
    buttons["4"] = ButtonState{{37,  245}}; 
    buttons["5"] = ButtonState{{141, 245}}; 
    buttons["6"] = ButtonState{{245, 245}}; 
    buttons["*"] = ButtonState{{349, 245}}; 
    // row 316 
    buttons["1"] = ButtonState{{37,  316}}; 
    buttons["2"] = ButtonState{{141, 316}}; 
    buttons["3"] = ButtonState{{245, 316}}; 
    buttons["/"] = ButtonState{{349, 316}}; 
    // row 387 
    buttons["0"] = ButtonState{{37,  387}}; 
    buttons["."] = ButtonState{{141, 387}}; 
    buttons["="] = ButtonState{.pos = {245, 387}, .size = {198, 60}};
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


void draw_numpad(sf::RenderTarget& win, const std::map<std::string,ButtonState> buttons) {
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
        // make it slightly darker
        const float scale = (float)button.second.border_scale / 255.f;
        button_bg -= Color{50,50,50,0} * ((float)button.second.color_scale / 255.f);
        border_col += border_col * scale;
        const float final_border_thickness = 
            Interpolation::EasingFunc::easeOutElastic(scale) * border_thickness * 2 + border_thickness;

        // draw the border
        Calc::Shape::CreateRoundedRect(button_vertex, vect_count, r + border_thickness,
                sf::Vector2f{button.second.size.x + final_border_thickness * 2,
                             button.second.size.y + final_border_thickness * 2},
                sf::Vector2f{button.second.pos.x - final_border_thickness,
                             button.second.pos.y - final_border_thickness},
                border_col);
        win.draw(button_vertex);

        // draw the button bg
        Calc::Shape::CreateRoundedRect(button_vertex, vect_count, r, button.second.size, button.second.pos, button_bg);
        win.draw(button_vertex);


        // prepare the text, and make sure its centered
        t.setString(button.first);
        t.setPosition(button.second.pos + (.5f * button.second.size));
        auto tbound = t.getLocalBounds();
        t.setOrigin(tbound.size / 2.f);
        
        win.draw(t);
    }

}

