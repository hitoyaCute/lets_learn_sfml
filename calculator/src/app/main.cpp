#include <array>
#include <cstdio>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "event.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "ui/shapes/basicShape.hpp"

#define unpack_vector2(ver) (ver).x, (ver).y

void update_cursor(sf::VertexArray& arr, const sf::Vector2f& pos);
void setFillColor(sf::VertexArray& arr, const sf::Color& col);

int main() {
    printf("sf::RenderTexture::getMaximumAntiAliasingLevel() = %d\n", sf::RenderTexture::getMaximumAntiAliasingLevel());
    sf::RenderWindow window{sf::VideoMode(conf::window_size), "Calculator", sf::Style::None};
    sf::RenderTexture wintex{conf::window_size};
    wintex.setSmooth(true);

    sf::Texture texture{sf::Image(conf::window_size,sf::Color::White)};//this is can also be updated to the correct size later, but might be helpful for debugging now
    texture.setSmooth(true);

    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);

    std::array<ButtonState, 19> buttons;
    setup_numpad(buttons);

    sf::Sprite sprite (texture);

    sf::CircleShape circle(16,16);
    
    sf::VertexArray cursor{sf::PrimitiveType::TriangleFan, 7};
    setFillColor(cursor, sf::Color::White);

    sf::Vector2f pos;
    while (window.isOpen()) {
        window.clear(conf::bg);
        wintex.clear(conf::bg);

        process_event(window, buttons);
        
        pos = (sf::Vector2f)sf::Mouse::getPosition(window);
        update_cursor(cursor, pos);

        draw_numpad(wintex,buttons);
        // draw_numdisplay(window);
        
        wintex.draw(circle);
        wintex.draw(cursor);
        wintex.display();

        texture.update(wintex.getTexture());

        window.draw(sprite);
        window.display();
    }
}

void setFillColor(sf::VertexArray& arr, const sf::Color& col) {
    for (size_t i = 0; i < arr.getVertexCount(); ++i) {
        arr[i].color = col;
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
