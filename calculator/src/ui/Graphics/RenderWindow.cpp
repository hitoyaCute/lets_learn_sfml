#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Color.hpp"
#include "Drawable.hpp"
#include "Interactable.hpp"
#include "RerderWindow.hpp"

using namespace Calc::Graphics;

RenderWindow::RenderWindow(sf::RenderWindow& window):
    window_ref(&window) {
    pickingWindow = {window.getSize()};
}

void RenderWindow::draw(Calc::Graphics::Drawable& drawable, const sf::RenderStates& states) {
    drawable.draw(*window_ref, states);
}
void RenderWindow::draw(InteractableElement& drawable, const sf::RenderStates& states) {
    drawable.draw(*this, states);
}
void RenderWindow::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
    window_ref->draw(drawable, states);
}
void RenderWindow::add_elemref(InteractableElement& element) {
    // cast the pointer to a Color type 
    const Color id = Color{&element};
    elements[id] = &element;
}

void RenderWindow::clear_elembuf() {
    elements.clear();
}
void RenderWindow::clear(const Color& col) {
    window_ref->clear(col);
    pickingWindow.clear(sf::Color::Black);
}

void RenderWindow::display() {
    window_ref->display();
    pickingWindow.display();
}

InteractableElement* RenderWindow::get_elem_under(const sf::Vector2i& pos) {
    return fetch_element(getPixel(pos));
}

class InteractableElement* RenderWindow::fetch_element(const Graphics::Color& id) {
    auto it = elements.find(id);

    if (it == elements.end()) {
        return 0;
    } else {
        return it->second;
    }
}

const Color RenderWindow::getPixel(const sf::Vector2i& pos) {
    const sf::Image& img = pickingWindow.getTexture().copyToImage();
    return img.getPixel(static_cast<sf::Vector2u>(pos));
}



