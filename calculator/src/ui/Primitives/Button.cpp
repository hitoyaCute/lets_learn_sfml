#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Button.hpp"
#include "ui/Graphics/Color.hpp"
#include "ui/Graphics/RenderTarget.hpp"
#include "util/time.hpp"

namespace Calc {
namespace Primitive {


Button::Button(const std::string& name):
    bound{0,0},
    position{0,0},
    tag{name}

{}

void Button::draw(Graphics::RenderTarget& window, const sf::RenderStates& state) {
    // create a rect
    sf::RectangleShape bg(this->bound);
    bg.setPosition(this->position);
    auto font = sf::Font(RES_DIR "fonts/NerdFonts/HackNerdFontMono-Regular.ttf");
    sf::Text text{font, this->tag, 20};
    text.setFillColor(sf::Color::Black);
    // draw the text somewhere on its center
    switch (this->state) {
        case State::normal: {
            bg.setFillColor(sf::Color{50,50,50});
            sf::Text text{font, this->tag, 20};
            break;
        } case State::hovering: {
            bg.setFillColor(sf::Color::Yellow);
            sf::Text text{font, this->tag + " hover", 20};
            break;
        } case State::pressed: {
            bg.setFillColor(sf::Color::Red);
            sf::Text text{font, this->tag, 20};
            break;
        } case State::clicked: {
            bg.setFillColor(sf::Color::Green);
            sf::Text text{font, this->tag + " clicked", 20};
            break;
        } case State::dragging: {
            bg.setFillColor(sf::Color::Blue);
            sf::Text text{font, this->tag+" is dragging", 20};
            break;
        }
    }
    this->state = State::normal;
    window.draw(bg, state);
    // draw the name of the button
    text.setPosition(this->position + this->bound / 2.f);
    window.draw(text, state);
    bg.setFillColor(Graphics::Color(this));
    window.draw_bound(bg);
    // window.
}

void Button::callback(const Calc::Window::Interaction_state& state) {
    // check if the button is clicked
    if (state.event == Window::Interaction_state::event_type::left_down) {
        this->state_raw = Time.time() * 10;

        this->state = State::pressed;
    } else if (state.event == Window::Interaction_state::event_type::hovering) {
        if (this->state != State::pressed) {
            this->state = State::hovering;
        }
        if (this->state_raw - Time.time() * 10 > 5 and this->state == State::dragging) {
            this->state = State::dragging;
        }
    } else if (state.event == Window::Interaction_state::event_type::left_up) {
        // check if the left_down is short enough
        if (this->state_raw - Time.time() * 10 <= 5) {
            this->state = Button::State::clicked;
        } else {
            this->state = State::normal;
        }
        this->state_raw = 0;
    } else {
        this->state = State::normal;
    }
}

void Button::setBound(const sf::Vector2f& bound, const sf::Vector2f& pos) {
    this->bound = bound;
    this->position = pos;
}


}; // namespace Primitive
}; // namespace Calc



