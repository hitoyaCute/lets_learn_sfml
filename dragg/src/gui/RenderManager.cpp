#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <SFML/Graphics/Image.hpp>
#include "RenderManager.hpp"

namespace MEU {

Drawable::Drawable(sf::VertexArray& arr, const size_t size_, const sf::Color id_, const sf::Vector2f pos):
  object{&arr},
  size{size_},
  id{id_},
  position({0,0}){
  objBound = new sf::VertexArray(object->getPrimitiveType(), size_);
  for (size_t i{size_}; i--;) {
    (*objBound)[i].position = (*object)[i].position;
    (*objBound)[i].color = id_;
  }

  setPosition(pos);
}

Drawable::Drawable(sf::VertexArray& arr, const size_t size_, const sf::Vector2f pos):
  object{&arr},
  size(size_),
  position({0,0}){
  setPosition(pos);
}



void Drawable::setPosition(sf::Vector2f pos) {
  const sf::Vector2f offset{position - pos};
  position = pos;
  for (size_t i{size}; i--;) {
    if (objBound) (*objBound)[i].position -= offset;
    (*object)[i].position -= offset;
  }
}
void Drawable::setFillColor(const sf::Color col) {
  for (size_t i{size}; i--;) {
    (*object)[i].color = col;
  }
}


sf::VertexArray& sfShapeToVertexArray(const sf::Shape& shape, size_t size, sf::Color fill_color) {
  auto* outArray = new sf::VertexArray{sf::PrimitiveType::TriangleFan, size};
  
  for (size_t i{size}; i--;) {
    (*outArray)[i].position = shape.getPoint(i);
    (*outArray)[i].color = fill_color;
  }

  return *outArray;
}

Renderer::Renderer(sf::Vector2u size, std::string title, sf::State state):
  target{sf::VideoMode{size}, title, state},
  pickingBuffer{size}{

  target.setFramerateLimit(3);
}

void Renderer::setFramerateLimit(unsigned int fps) {
  target.setFramerateLimit(fps);
}

void Renderer::clear(sf::Color color) {
  target.clear(color);
  pickingBuffer.clear(sf::Color::Black);
}

void Renderer::draw(const Drawable& drawable, const sf::RenderStates& states) {
  target.draw(*drawable.object, states);
}

void Renderer::ObjDraw(const Drawable& drawable, const sf::RenderStates& states) {
  if (drawable.objBound == nullptr or drawable.object == nullptr) {
    throw std::runtime_error("uhhh you missed the part where you forgot to give pointer to a object at Renderer::ObjDraw(const Drawable&, const sf::RenderStates)");
  }
  target.draw(*drawable.object, states);
  pickingBuffer.draw(*drawable.objBound);
}

void Renderer::setVerticalSyncEnabled(bool enabled){
  target.setVerticalSyncEnabled(enabled);
}

bool Renderer::isOpen() {
  return target.isOpen();
}

void Renderer::close() {
  target.close();
}

std::optional<sf::Event> Renderer::pollEvent(){
  return target.pollEvent();
}

sf::WindowBase& Renderer::getWindowRef(){
  return target;
}

Drawable* Renderer::getItem(std::unordered_map<size_t, Drawable*>& ObjectLists) {
  
  const auto mousePos = sf::Mouse::getPosition(target);
  // check if the curser was out-bound/outside the render target
  if (mousePos.x < 0 || mousePos.y < 0 ||
      mousePos.x >= (int)target.getSize().x ||
      mousePos.y >= (int)target.getSize().y)
        return nullptr;
  
  // else
  const sf::Image image = pickingBuffer.getTexture().copyToImage();
  
  const sf::Color match = image.getPixel({(uint32_t)mousePos.x, (uint32_t)mousePos.y});
  // color hashing
  const size_t match_id = (match.r << 16) | (match.g << 8) | match.b;

  
  Drawable* output = ObjectLists[match_id];
  
  
  return output;
}

void Renderer::display(){
  target.display();
  pickingBuffer.display();
}

}; // namepsace MEU







