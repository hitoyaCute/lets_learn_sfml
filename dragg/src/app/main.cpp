#include <random>
#include <ostream>
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "gui/Shapes/Shapes.hpp"
// #include "range"
#include "config.hpp"
#include "gui/RenderManager.hpp"
#include "gui/Viewport.hpp"
// #include "gui/Events/events.hpp"
// #include "gui/Interpolated/Interpolated.hpp"

int main(){
  MEU::Renderer<sf::RenderWindow> window{conf::win_size, "viewport", sf::State::Fullscreen};
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  
  sf::View v{sf::Vector2f{500,500}/2.f,{500,500}};

  MEU::ViewPort viewport_{sf::VertexArray{sf::PrimitiveType::TriangleFan, 8*4}, {2000,2000}};


  viewport_.setView(v);
  MEU::Drawable circlea{MEU::sfShapeToVertexArray(sf::CircleShape(100,16), 16), 16, {0.f,0.f}};
  circlea.setFillColor(sf::Color::Red);
  circlea.setPosition({100,-100});
  
  viewport_.draw(circlea);
  
  viewport_.clear();
  viewport_.draw(circlea);
  viewport_.display();


  const sf::Texture* vv_img = &viewport_.getTexture();
  auto vv_size = sf::Vector2f{viewport_.getSize()};

  // thing that will hold the Texture

  // auto viewport = MEU::sfShapeToVertexArray(sf::RectangleShape{{500,500}}, 4, sf::Color{255,255,255});
  sf::VertexArray viewport{sf::PrimitiveType::TriangleFan, 8*4};
  MEU::CreateRoundedRect(viewport, 8*4, 50, {500,500}, {0,0});
  
  MEU::apply_texture(viewport, 8*4, vv_size);

  MEU::Drawable viewport_drawable{viewport, 8*4, {100,100}};
  // objects
  // sf::CircleShape obj1{50.f,50};
  // MEU::Drawable OBJ1{MEU::sfShapeToVertexArray(obj1, 50, sf::Color{255,0,0,175}),
  //                    50,
  //                    sf::Color{0,0,1},
  //                    {100,100}};

  // sf::CircleShape obj2{70.f, 50};
  // MEU::Drawable OBJ2{MEU::sfShapeToVertexArray(obj2, 50, sf::Color{0,0,255,175}),
  //                    50,
  //                    sf::Color{0,0,2},
  //                    {300,300}};
  
  std::unordered_map<size_t, MEU::Drawable*> objLists{};
  // objLists[1] = &OBJ1;
  // objLists[2] = &OBJ2;

  // random generator
  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, 255);
  
  MEU::Drawable* selected;
  sf::Vector2f offset;

  while (window.isOpen()) {

    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (const auto key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }

      if (const auto button = event->getIf<sf::Event::MouseButtonPressed>()) {
        const auto mousePos = sf::Mouse::getPosition(window.getWindowRef());
        
        MEU::Drawable* picked = window.getItem(objLists, mousePos);
        if (button->button == sf::Mouse::Button::Left) {
        // Start dragging if clicked object
          if (picked) {
            selected = picked;
            offset = picked->position - sf::Vector2f(mousePos);
          }
        } else if (button->button == sf::Mouse::Button::Right) {
          // Randomize color if right-clicked object
          if (picked) {
            picked->setFillColor(sf::Color(dist(rng), dist(rng), dist(rng), 175));
          }
        }
      }
      
      if (auto button = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (button->button == sf::Mouse::Button::Left) {
          selected = nullptr; // stop dragging
        }
      }

      if (const auto* mouse = event->getIf<sf::Event::MouseMoved>()) {
        if (selected){
          std::cout << selected << std::endl;
          selected->setPosition(sf::Vector2f(mouse->position) + offset);
        }
      }
    }

    window.clear(sf::Color::White);
    sf::RenderStates states;
    // states.transform.translate(vv_size * 0.5f);
    states.texture = vv_img;
    
    // Normal drawing with visible colors
    window.draw(viewport_drawable, states);
    // window.ObjDraw(OBJ1);
    // window.ObjDraw(OBJ2);
    window.display();
  }
}


