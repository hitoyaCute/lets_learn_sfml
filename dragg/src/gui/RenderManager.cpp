#include <unistd.h>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "RenderManager.hpp"

namespace MEU {

constexpr sf::VertexArray sfShapeToVertexArray(const sf::Shape& shape, size_t size, sf::Color fill_color) {
  sf::VertexArray outArray{sf::PrimitiveType::TriangleFan, size};
  
  for (size_t i{size}; i--;) {
    outArray[i].position = shape.getPoint(i);
    outArray[i].color = fill_color;
  }

  return outArray;
}

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

/*////////////////////////////////////////////////////////////

                      Renderer

////////////////////////////////////////////////////////////*/
template<>
Renderer<sf::RenderWindow>::Renderer(sf::Vector2u size, std::string title, sf::State state):
  target(sf::VideoMode{size}, title, state),
  pickingBuffer{size}{}

template<>
Renderer<sf::RenderTexture>::Renderer(sf::Vector2u size):
  target(size),
  pickingBuffer(size){}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
void Renderer<sf::RenderWindow>::setFramerateLimit(unsigned int fps) {
  target.setFramerateLimit(fps);
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
void Renderer<sf::RenderWindow>::setVerticalSyncEnabled(bool enabled){
  target.setVerticalSyncEnabled(enabled);
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
bool Renderer<sf::RenderWindow>::isOpen() {
  return target.isOpen();
}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
void Renderer<sf::RenderWindow>::close() {
  target.close();
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
std::optional<sf::Event> Renderer<sf::RenderWindow>::pollEvent(){
  return target.pollEvent();
}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
template<>
sf::WindowBase& Renderer<sf::RenderWindow>::getWindowRef(){
  return target;
}
////////////////////////////////////////////////////////////

}; // namepsace MEU

