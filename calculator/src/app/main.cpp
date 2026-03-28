#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
    window.setPosition({0,0});
    // window.setVerticalSyncEnabled(true);
    
    // global button ref
    std::array<ButtonState, 19> buttons;
    setup_numpad(buttons);

    sf::RenderTexture tempText{{1600,1600}};
    tempText.setSmooth(1);

    sf::VertexArray cursor{sf::PrimitiveType::TriangleFan, 7};
    setFillColor(cursor, sf::Color::Blue);
    update_cursor(cursor, {200.f,200.f});
    
    sf::VertexArray c{sf::PrimitiveType::TriangleFan, 8 * 4};

    Calc::Shape::CreateRoundedRect(c, 8*4, 208.f, {800,600}, {400,400}, sf::Color::White);
    tempText.draw(c);
    Calc::Shape::CreateRoundedRect(c, 8*4, 200.f, {800,600}, {400,400}, sf::Color::Blue);
    tempText.draw(c);
    tempText.draw(cursor);
    tempText.display();
    sf::Sprite sp{tempText.getTexture()};
    sp.setScale({0.125,0.125});

    // sf::Vector2f pos;
    while (window.isOpen()) {
        window.clear(conf::bg);

        process_event(window, buttons);
        // pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        // update_cursor(cursor, pos * 2.f);

        draw_numpad(window,buttons);
        draw_numdisplay(window, "AAAAAAA.A");
        
        window.draw(sp);
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
