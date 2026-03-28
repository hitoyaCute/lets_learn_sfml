#include "event.hpp"
#include "Interpolated/Interpolated.hpp"
#include "app/helpers.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <cstdio>
#include <array>
#include <initializer_list>
#include <ostream>
#include <unordered_set>

ButtonState* get_button_at(const sf::Vector2f& pos, std::array<ButtonState, 19>& buttons) {
    for (size_t i =0; i < buttons.size(); i++){
        if (sf::Rect<float>{buttons[i].pos, buttons[i].size}.contains(pos)) {
            return &buttons[i];
        }
    }
    return 0;
}

ButtonState* find_button(const std::string& d, std::array<ButtonState, 19>& buttons) {
    for (auto& b: buttons) {
        if (b.name == d) return &b;
    }
    return 0;
}

template <typename T>
const inline bool is_in(const T& d, const std::initializer_list<T> arr) {
    return std::ranges::find(arr, d) != arr.end();
}
const inline bool is_in(const char& d, const char* arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == d) return true;
    }
    return false;
}
const inline bool calc_is_valid(const char c) {
    if ('A' <= c and c <= 'Z') return true;
    if ('0' <= c and c <= '9') return true;
    if (is_in(c, "/*+-")) return true;
    return false;
}

void process_event(sf::RenderWindow &win, std::array<ButtonState, 19>& buttons) {
    // process events
    static std::unordered_set<sf::Keyboard::Key> holded_key;
    
    std::unordered_set<std::string> entered;
    static std::unordered_set<std::string> pressed;
    while (const auto event = win.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            #ifdef debug
            printf("\x1b[%luB", std::size(buttons)*99);
            fflush(stdout);
            #endif
            win.close();
            return;
        }
        else if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
            using namespace sf::Keyboard;
            if (key->scancode == sf::Keyboard::Scancode::Escape) {

                #ifdef debug
                printf("\x1b[%luB", std::size(buttons)*99);
                fflush(stdout);
                #endif
                win.close();
                return;
            } else {
                holded_key.insert(key->code);
            }
        } else if (const auto key = event->getIf<sf::Event::KeyReleased>()) {
            holded_key.erase(key->code);
        } else if (auto text = event->getIf<sf::Event::TextEntered>()) {
            entered.insert(sf::String{text->unicode});
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
            ButtonState* button = get_button_at(mouse_pos, buttons);
            if (button and mouse->button == sf::Mouse::Button::Left) {
                // printf("pressed\n");
                // button->is_click = true;
                // button->color_scale = -1;
                pressed.insert(button->name);
            }
        } else if (const auto mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
            auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
            ButtonState* button = get_button_at(mouse_pos, buttons);
            if (button and mouse->button == sf::Mouse::Button::Left) {
                // printf("released\n");
                // button->is_click = false;
                // button->color_scale.reset(0);
                pressed.erase(button->name);
            }
        }
    }

    auto mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(win);
    // restore all if needed
    for (auto& button: buttons) {
        const bool inside = sf::FloatRect{button.pos, button.size}.contains(mouse_pos);
        // handles all numbers
        const bool in_hold_key = holded_key.contains(button.activation_key) or pressed.contains(button.name);
        bool hold =  button.is_click;
        if (in_hold_key and not button.is_click) {
            hold = true;
            holded_key.erase(button.activation_key);
            // button.color_scale = -1;
        } else if (not in_hold_key and button.is_click) {
            hold = false;
        }

        if (entered.contains(button.name) or (int(button.activation_key) == -1 and button.is_click)) {
            hold = true;
        }
        
        if(not inside and button.is_hover) {
            button.is_hover = false;
            hold = hold or false;
            button.border_scale.reset(0);
            // if (not hold) {
                pressed.erase(button.name);
            // }
        }
        else if(inside and not button.is_hover) {
            button.is_hover = true;
            button.border_scale = -1;
        }
        button.is_click = hold;
        #ifdef debug
        printf("%d:%s\n", button.is_click, button.name.c_str());
        #endif
    }
    #ifdef debug
    printf("\x1b[%luA", std::size(buttons));
    fflush(stdout);
    #endif
}

