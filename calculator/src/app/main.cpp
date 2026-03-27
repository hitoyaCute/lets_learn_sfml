#include <array>
#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderStates.hpp>


#include "event.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"

#define unpack_vector2(ver) (ver).x, (ver).y
void update_cursor(sf::VertexArray& arr, const sf::Vector2f& pos);

int main() {
    sf::RenderWindow window{sf::VideoMode(conf::window_size), conf::project_name, sf::Style::None};
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);
    
    // global button ref
    std::array<ButtonState, 19> buttons;
    setup_numpad(buttons);


    // sf::VertexArray cursor{sf::PrimitiveType::TriangleFan, 7};
    // setFillColor(cursor, sf::Color{200,200,200});

    // sf::Vector2f pos;
    while (window.isOpen()) {
        window.clear(conf::bg);

        process_event(window, buttons);
        // pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        // update_cursor(cursor, pos);

        draw_numpad(window,buttons);
        draw_numdisplay(window, " ");
        
        // window.draw(cursor);
        window.display();
    }
}

void update_cursor(sf::VertexArray& arr, const sf::Vector2f& pos) {
    // length check
    if (arr.getVertexCount() != 7 or arr.getPrimitiveType() != sf::PrimitiveType::TriangleFan)
        return;

    arr[0].position = pos + sf::Vector2f{ 0.00, 0.0};
    arr[1].position = pos + sf::Vector2f{ 0.00,12.0};
    arr[2].position = pos + sf::Vector2f{ 4.20,12.0};
    arr[3].position = pos + sf::Vector2f{ 5.75,17.0};
    arr[4].position = pos + sf::Vector2f{ 8.75,17.0};
    arr[5].position = pos + sf::Vector2f{ 7.20,12.0};
    arr[6].position = pos + sf::Vector2f{11.00,12.0};
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
