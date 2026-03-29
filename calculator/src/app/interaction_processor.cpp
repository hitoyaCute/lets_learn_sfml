#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


#include "app/event.hpp"
#include "app/helpers.hpp"


using namespace sf::Keyboard;
constexpr sf::Event::KeyPressed to_KeyCode(const std::string i) {
    // operators
    if (i == "+") return {.scancode = Scan::Equal, .shift = 1};
    if (i == "-") return {.scancode = Scan::Hyphen};
    if (i == "*") return {.scancode = Scan::Num8, .shift = 1};
    if (i == "/") return {.scancode = Scan::Slash};
    // special button 
    // convert the current value into percentage
    if (i == "%") return {.scancode = Scan::Num5, .shift = 1};
    // evaluates
    if (i == "=") return {.scancode = Scan::Equal};
    // remove 1 character at back and decrement decimal point
    if (i == "Del") return {.scancode = Scan::Backspace};
    // clear everything
    if (i == "C") return {.scancode = Scan::C};
    if (i == ".") return {.scancode = Scan::Period};
    // numbers

    if (i == "0") return {.scancode = Scan::Num0};
    if (i == "1") return {.scancode = Scan::Num1};
    if (i == "2") return {.scancode = Scan::Num2};
    if (i == "3") return {.scancode = Scan::Num3};
    if (i == "4") return {.scancode = Scan::Num4};
    if (i == "5") return {.scancode = Scan::Num5};
    if (i == "6") return {.scancode = Scan::Num6};
    if (i == "7") return {.scancode = Scan::Num7};
    if (i == "8") return {.scancode = Scan::Num8};
    if (i == "9") return {.scancode = Scan::Num9};

    return {};
}


void update_buttons(sf::RenderWindow& win, std::array<ButtonState, 19>& buttons, void (*handle_event)(event event_info)) {
    const auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
    for (auto& button: buttons) {

        // check if the cursor is abouve the button
        bool hovering = false;
        hovering = sf::FloatRect{button.pos, button.size}.contains(mouse_pos);
        if (hovering and not button.is_hover) {
            button.is_hover = 1;
            button.border_scale = -1;
        } else if (not hovering and button.is_hover) {
            button.is_hover = 0;
            button.border_scale.reset(0);
        }       
        // check for button press
        
        // pressed by keyboard
        const auto current_button = to_KeyCode(button.name);
        // the button is currently being hold
        bool key_hold = sf::Keyboard::isKeyPressed(current_button.scancode) and not (current_button.shift ^ sf::Keyboard::isKeyPressed(Scan::LShift));
        // pressed by mouse
        bool mouse_hold = false;
        if (hovering and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            mouse_hold = 1;
        }

        if (not button.is_click and (key_hold or mouse_hold)) {
            // printf("'%s' is pressed\n",button.name.c_str());
            handle_event({button.name, 1});
            button.is_click = 1;
        } else if (button.is_click and not (key_hold or mouse_hold)) {
            // printf("'%s' is released\n",button.name.c_str());
            button.is_click = 0;
        }
    }
}




