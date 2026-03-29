#include <array>
#include <cctype>
#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cstdlib>
#include <string>


#include "event.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"

#define unpack_vector2(ver) (ver).x, (ver).y
void update_cursor(sf::VertexArray& arr, const sf::Vector2f& pos);

struct GlobalState {
    // stuff to draw on the screen
    std::string view = "0";
    float A, B, result;
    // + add
    // - sub
    // / div
    // * mul
    // 
    // 0 no operator
    char ope = '\0';

    bool dot_applied = false;

    bool A_is_entered = false;
    // only reset will be ussable
    bool done = false;


} static CalcState{};

bool is_all_digits(const std::string& s) {
    if (s.empty()) return false;
    for (char c: s) {
        if ((c < '0' or c > '9') and c != '.') return false;
    }
    return true;
}
inline float parse_to_float(const std::string& d) {
    return atof(d.c_str());
}

void event_handler(const event event_type) {
    auto& name = event_type.name;
    auto& view = CalcState.view;
    auto& ope = CalcState.ope;
    auto& A_is_entered = CalcState.A_is_entered;
    if (CalcState.done or name == "C") {
        CalcState = GlobalState{};
    } else if (is_all_digits(name) and name != ".") {
        if (view.length() >= 6){}
        else {
            if (view == "0" or not is_all_digits(view)) {
                view = name;
            } else
            view += name;
        }
    } else if (not CalcState.dot_applied and name == ".") {
        view += ".";
        CalcState.dot_applied = 1;
    } else if (name == "Del") {
        if (view.length() == 1) {
            view = "0";
        } else
        view.pop_back();
    } else if (name == "+") {
        CalcState.A = parse_to_float(view);
        view = "+";
        ope = '+';
        A_is_entered = 1;
    } else if (name == "-") {
        if (not A_is_entered) CalcState.A = parse_to_float(view);
        view = "-";
        ope = '-';
        A_is_entered = 1;
    } else if (name == "*") {
        if (not A_is_entered) CalcState.A = parse_to_float(view);
        view = "*";
        ope = '*';
        A_is_entered = 1;
    } else if (name == "/") {
        if (not A_is_entered) CalcState.A = parse_to_float(view);
        view = "/";
        ope = '/';
        A_is_entered = 1;
    }  else if (name == "%" and not A_is_entered) {
        view = std::to_string(parse_to_float(view) / 100.f);
        ope = '%';
        CalcState.done = 1;
    }
}



int main() {
    sf::RenderWindow window{sf::VideoMode(conf::window_size), conf::project_name, sf::Style::None};
    window.setFramerateLimit(60);
    window.setPosition({0,0});
    // window.setVerticalSyncEnabled(true);
    
    // global button ref
    std::array<ButtonState, 19> buttons;
    setup_numpad(buttons);

    // sf::Vector2f pos;
    while (window.isOpen()) {
        window.clear(conf::bg);
        process_event(window); // raw events
        update_buttons(window, buttons, event_handler); // process user interactions to the buttons
        // pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        // update_cursor(cursor, pos * 2.f);

        draw_numpad(window,buttons);
        draw_numdisplay(window, CalcState.view);
        
        window.display();
    }
}

void update_cursor(sf::VertexArray& arr, const sf::Vector2f& pos) {
    // length check
    if (arr.getVertexCount() != 7 or arr.getPrimitiveType() != sf::PrimitiveType::TriangleFan)
        return;

    arr[0].position = pos + sf::Vector2f{ 0.00, 0.0} * 8.f;
    arr[1].position = pos + sf::Vector2f{ 0.00,12.0} * 8.f;
    arr[2].position = pos + sf::Vector2f{ 4.20,12.0} * 8.f;
    arr[3].position = pos + sf::Vector2f{ 5.75,17.0} * 8.f;
    arr[4].position = pos + sf::Vector2f{ 8.75,17.0} * 8.f;
    arr[5].position = pos + sf::Vector2f{ 7.20,12.0} * 8.f;
    arr[6].position = pos + sf::Vector2f{11.00,12.0} * 8.f;
}







/*




/
//
/ /
/   /
/     /
/       /
/         /
/           /
/             /
/               /
/                 /
/                    /
////////     //////////
        /     /
         /     /
          /     /
           /     /
            ///////

0,0
12,0
12,7
17,12
17,18
12,13
12,22


*/
