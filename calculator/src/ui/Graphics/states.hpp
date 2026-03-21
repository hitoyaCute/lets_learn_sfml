#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Calc {
namespace Window {

// struct that holds the copy of the current state of the user
struct Interaction_state {
    // extra state
    enum class mode {
        // mode when editing
        Insert,
        // mode on normal operation
        Normal,
        //
        Visual,
    };
    enum class event_type {      
        key_up,
        key_down,

        left_down,
        right_down,
        middle_down,
        left_up,
        right_up,
        middle_up,
        // built-in that tells when the mouse is just hovering
        hovering,
        // built-in state that tells the user is at dragging state
        // its when the left_down is 
        dragging,
        scrolling,
    };

    mode current_mode = mode::Normal; 
    
    event_type event = event_type::hovering;

    sf::Keyboard::Key key_event_values;
    sf::Mouse::Button mouse_event_value;
    sf::Mouse::Wheel wheel_event_value;
    sf::Vector2i mouse_position_value = {0,0};

    float time_since_ldown = 0;
    float wheel_delta      = 0;
}; // struct Interaction_state

}; // namespace Window
}; // namesapce Calc


