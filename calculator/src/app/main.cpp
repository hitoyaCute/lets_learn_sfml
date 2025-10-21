#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include "config.hpp"
#include "ui/event/events.hpp"


int main() {
    sf::RenderWindow window{sf::VideoMode(conf::window_size), "Calculator", sf::State::Fullscreen};

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        
        Calc::process_event(window);





        
    }





}





