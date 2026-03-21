#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include "app/window.hpp"
#include "config.hpp"
#include "ui/Graphics/Color.hpp"
#include "ui/Graphics/RerderWindow.hpp"
#include "ui/Primitives/Button.hpp"

int main() {
    sf::RenderWindow window{sf::VideoMode(conf::window_size), "Calculator", sf::State::Fullscreen};
    Calc::Graphics::RenderWindow window_manager(window);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Calc::Primitive::Button a{"Button"};
    a.setBound({150,50},{100,150});
    printf("%08x \n", Calc::Graphics::Color(&a).rgba());
    printf("%08x \n", Calc::Graphics::Color(sf::Color::Black).rgba());
    window_manager.add_elemref(a);

    while (window.isOpen()) {
        window_manager.clear(sf::Color::White);

        // draw
        window_manager.draw(a);
        window_manager.display();

        // process events
        Calc::Window::process_event(window,window_manager);

    }
}

