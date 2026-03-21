#include <memory>
#include <unistd.h>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "RenderManager.hpp"
#include "gui/Drawable.hpp"

namespace MEU {

sf::VertexArray sfShapeToVertexArray(const sf::Shape& shape, size_t size, sf::Color fill_color) {
  sf::VertexArray outArray{sf::PrimitiveType::TriangleFan, size};
  
  for (size_t i{size}; i--;) {
    outArray[i].position = shape.getPoint(i);
    outArray[i].color = fill_color;
  }

  return outArray;
}
void apply_texture(sf::VertexArray& arr,
                             const uint32_t vertex_ammount,
                             const sf::Vector2f texture_size) {
  //////////////////////////////////////////////////////////////
  sf::Vector2f arr_size = arr.getBounds().size;

  for (uint8_t j{0}; j < vertex_ammount; j++) {
    sf::Vector2f current_vertex_pos = arr[j].position;
    float ratio_x = current_vertex_pos.x / arr_size.x; // the ammounf of the vertex.x is placed before reaching the size.x
    float ratio_y = current_vertex_pos.y / arr_size.y; // the ammounf of the vertex.y is placed before reaching the size.y
    arr[j].texCoords = {ratio_x * texture_size.x, ratio_y * texture_size.y};
  }
}

Drawable::Drawable(const sf::VertexArray& arr, const size_t size_, const sf::Color id_, const sf::Vector2f pos):
  object{arr},
  size{size_},
  id{id_},
  position({0,0}){
   
  objBound = std::make_unique<sf::VertexArray>(object.getPrimitiveType(), size_);
  for (size_t i{size_}; i--;) {
    (*objBound)[i].position = object[i].position;
    (*objBound)[i].color = id_;
  }
  setPosition(pos);
}

Drawable::Drawable(const sf::VertexArray& arr, const size_t size_, const sf::Vector2f pos):
  object{arr},
  size(size_),
  position({0,0}){
  setPosition(pos);
}

void Drawable::setPosition(sf::Vector2f pos) {
  const sf::Vector2f offset{position - pos};
  position = pos;
  for (size_t i{size}; i--;) {
    if (objBound) (*objBound)[i].position -= offset;
    object[i].position -= offset;
  }
}

void Drawable::setFillColor(const sf::Color col) {
  for (size_t i{size}; i--;) {
    object[i].color = col;
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

