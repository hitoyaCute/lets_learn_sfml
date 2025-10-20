#include <cmath>
#include <SFML/Graphics/Drawable.hpp>
#include "basicShape.hpp"



namespace Calc {


CircleGenerator::CircleGenerator(uint32_t quality_, float radius_):
  radius{radius_},
  da{(2.0f * sf::priv::pi) / quality_}{};

constexpr sf::Vector2f CircleGenerator::get_point(uint32_t i) {
  const float angle = da * static_cast<float>(i);
  return {radius * sf::Vector2f{cosf(angle), sinf(angle)}};
}


RoundedRectGenerator::RoundedRectGenerator(sf::Vector2f size_, float radius_, uint32_t quality_):
  size{size_},
  radius{radius_},
  quality{quality_},
  da{(2.0f * sf::priv::pi) / (quality_-4)},
  centers{
    {size_.x - radius_, size_.y - radius_},
    {radius_          , size_.y - radius_},
    {radius_          , radius_},
    {size_.x - radius_, radius_}
  }{}

constexpr sf::Vector2f RoundedRectGenerator::get_point(uint32_t i) {
  const uint32_t idx{i / (quality / 4)};
  const float angle = da * (float)(i-idx);

  return centers[idx] + (radius * sf::Vector2f{cosf(angle), sinf(angle)});
}

///// functions

void CreateCircle(sf::VertexArray& arr,
                  uint32_t quality,
                  float radius,
                  sf::Vector2f pos,
                  sf::Color color) {
  CircleGenerator generator{quality, radius};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = pos + generator.get_point(i);
    arr[i].color = color;
  }
}

void CreateRoundedRect(sf::VertexArray& arr,
                       uint32_t quality,
                       float radius,
                       sf::Vector2f size,
                       sf::Vector2f pos,
                       sf::Color color) {
  RoundedRectGenerator generator{size, radius, quality};
  for (uint32_t i{0}; i < quality; i++) {
    arr[i].position = pos + generator.get_point(i);
    arr[i].color = color;
  }
}
void CreateRoundedRectBorder(sf::VertexArray& arr,
                             uint32_t quality,
                             float radius,
                             float thickness,
                             sf::Vector2f size,
                             sf::Vector2f pos,
                             sf::Color color_inner,
                             sf::Color color_outer){

  RoundedRectGenerator inner{size, radius, quality/2 - 1};
  RoundedRectGenerator outer{size + 2.f * sf::Vector2f{thickness, thickness}, radius+(thickness/2), quality/2 - 1};
  
  for (uint32_t i{0}; i < quality/2 - 1; i++) {

    arr[i*2].position = pos + inner.get_point(i);
    arr[i*2].color = color_inner;
    arr[i*2+1].position = pos + outer.get_point(i) - sf::Vector2f{thickness, thickness};
    arr[i*2+1].color = color_outer;
  }

  arr[quality-2].position = arr[0].position;
  arr[quality-2].color = arr[0].color;
  arr[quality-1].position = arr[1].position;
  arr[quality-1].color = arr[1].color;
}


}; // namespace Calc

