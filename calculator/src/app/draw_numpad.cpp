#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"
#include "Interpolated/Interpolated.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

void setup_numpad(std::vector<ButtonState>& buttons) {
    // array struct
    //     037 141 245 349
    // 103 Del  C   %   +
    // 174  7   8   9   -
    // 245  4   5   6   *
    // 316  1   2   3   /
    // 387  0   .   [ = ]
    
             // row 103                          
    buttons.emplace_back(sf::Vector2f{37.f,  103.f}, "Del");
    buttons.emplace_back(sf::Vector2f{141, 103}, "C");
    buttons.emplace_back(sf::Vector2f{245, 103}, "%"); 
    buttons.emplace_back(sf::Vector2f{349, 103}, "+"); 
    // row 174
    buttons.emplace_back(sf::Vector2f{37,  174}, "7"); 
    buttons.emplace_back(sf::Vector2f{141, 174}, "8"); 
    buttons.emplace_back(sf::Vector2f{245, 174}, "9"); 
    buttons.emplace_back(sf::Vector2f{349, 174}, "-"); 
    // row 245 
    buttons.emplace_back(sf::Vector2f{37,  245}, "4"); 
    buttons.emplace_back(sf::Vector2f{141, 245}, "5"); 
    buttons.emplace_back(sf::Vector2f{245, 245}, "6"); 
    buttons.emplace_back(sf::Vector2f{349, 245}, "*"); 
    // row 316 
    buttons.emplace_back(sf::Vector2f{37,  316}, "1"); 
    buttons.emplace_back(sf::Vector2f{141, 316}, "2"); 
    buttons.emplace_back(sf::Vector2f{245, 316}, "3"); 
    buttons.emplace_back(sf::Vector2f{349, 316}, "/"); 
    // row 387 
    buttons.emplace_back(sf::Vector2f{37,  387}, "0"); 
    buttons.emplace_back(sf::Vector2f{141, 387}, "."); 
    buttons.emplace_back(sf::Vector2f{245, 387}, sf::Vector2f{198, 60}, "=");
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


void draw_numpad(sf::RenderTarget& win, const std::vector<ButtonState>& buttons) {
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
        const float scale = (float)button.border_scale / 255.f;
        button_bg -= Color{50,50,50,0} * (float)button.color_scale;
        border_col += border_col * scale;
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
        t.setPosition(button.pos + (.5f * button.size));
        auto tbound = t.getLocalBounds();
        t.setOrigin(tbound.size / 2.f);
        
        win.draw(t);
    }
}

