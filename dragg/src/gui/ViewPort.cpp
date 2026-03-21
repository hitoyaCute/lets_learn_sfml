#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Viewport.hpp"
#include "RenderManager.hpp"
#include "gui/Drawable.hpp"

namespace  MEU {

ViewPort::ViewPort(sf::VertexArray surface_, sf::Vector2u size):
  target(size),
  surface{sfShapeToVertexArray(sf::RectangleShape{(sf::Vector2f)size}, 4)},
  pos{0.f,0.f},
  view((sf::Vector2f)size / 2.f, (sf::Vector2f)size){
}

void ViewPort::setView(const sf::View& view_) {
  view = view_;
}

void ViewPort::viewMove(const sf::Vector2f move) {
  view.move(move);
}

void ViewPort::draw(const Drawable& obj) {
  target.draw(obj);
}

void ViewPort::objDraw(const Drawable& obj) {
  target.ObjDraw(obj);
}


void ViewPort::setPos(const sf::Vector2f newpos) {
  pos = newpos;
}

void ViewPort::clear(const sf::Color& color) {
  target.clear(color);
}

void ViewPort::display() {
  target.display();
}

const sf::Texture& ViewPort::getTexture() const {
  return target.getTexture();
}

const sf::Vector2f& ViewPort::getSize() const {
  return target.getSize();
}

}; // namespace MEU

