#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "config.hpp"
#include "range"
#include "gui/RenderManager.hpp"
// #include "gui/Events/events.hpp"
// #include "gui/Interpolated/Interpolated.hpp"


int main(){
  MEU::Renderer window(conf::win_size, "viewport", sf::State::Fullscreen);
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  sf::CircleShape cc{60.f,50};
  
  sf::View v{{0,0},{100,100}};
  v.move({10,0});
  
  sf::RenderTexture vv{conf::win_size};
  vv.setView(v);
  sf::CircleShape circlea{};
  circlea.setRadius(10.f);
  circlea.setFillColor(sf::Color::Red);
  circlea.setPosition({0,0});

  vv.clear(sf::Color::Cyan);
  vv.draw(circlea);
  vv.display();

  const sf::Texture* vv_img = &vv.getTexture();
  const auto vv_size = sf::Vector2f{vv.getSize()};

  // thing that will hold the Texture
  auto viewport = MEU::sfShapeToVertexArray(sf::RectangleShape{{500,500}}, 4, sf::Color{255,255,255});
  
  viewport[0].texCoords = {0, 0};
  viewport[1].texCoords = {vv_size.x, 0};
  viewport[2].texCoords = {0, vv_size.y};
  viewport[3].texCoords = {vv_size.x, vv_size.y};
  MEU::Drawable viewport_drawable{viewport, 4, {100,100}};


  

  

  
  

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
        MEU::Drawable* picked = window.getItem(objLists);
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


