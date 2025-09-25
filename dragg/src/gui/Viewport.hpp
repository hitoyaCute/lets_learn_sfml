#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
// #include "Drawable.hpp"
#include "RenderManager.hpp"
#include "gui/Drawable.hpp"

namespace MEU {

/// viewport wrapper of Renderer
class ViewPort {
  Renderer<sf::RenderTexture> target;
  // the surface on where the texture will be placed
  sf::VertexArray surface;
  // position relative to the parent holder
  sf::Vector2f pos;
  // the view.....
  sf::View view;

public:
  ViewPort() = default;
  ////////////////////////////////////////////////////////////
  /// \constructor for the viewport
  ////////////////////////////////////////////////////////////
  ViewPort(sf::VertexArray surface_, sf::Vector2u size);
  ////////////////////////////////////////////////////////////
  /// \brief Change the current active view
  ///
  /// The view is like a 2D camera, it controls which part of
  /// the 2D scene is visible, and how it is viewed in the
  /// render target.
  /// The new view will affect everything that is drawn, until
  /// another view is set.
  /// The render target keeps its own copy of the view object,
  /// so it is not necessary to keep the original one alive
  /// after calling this function.
  /// To restore the original view of the target, you can pass
  /// the result of `getDefaultView()` to this function.
  ///
  /// \param view New view to use
  ///
  /// \see `getView`, `getDefaultView`
  ///
  ////////////////////////////////////////////////////////////
  void setView(const sf::View& view_);
  ////////////////////////////////////////////////////////////
  /// \brief Move the view and refresh of view
  ///
  /// \param direction the array of value to move the view
  ///
  ////////////////////////////////////////////////////////////
  void viewMove(const sf::Vector2f move);
  ////////////////////////////////////////////////////////////
  /// \brief Move the view and refresh of view
  ///
  /// \param direction the array of value to move the view
  ///
  ////////////////////////////////////////////////////////////
  void setPos(const sf::Vector2f new_pos);
  ////////////////////////////////////////////////////////////
  /// \brief draw to the viewport's buffer
  ///
  /// \param obj, the object that will be drawn to the buffer
  ///
  ////////////////////////////////////////////////////////////
  void draw(const Drawable& obj);
  ////////////////////////////////////////////////////////////
  /// \brief draw to the viewport's buffer and picking buffer
  ///
  /// \param obj, the object that will be drawn to the buffer
  ///
  ////////////////////////////////////////////////////////////
  void objDraw(const Drawable& obj);
  ////////////////////////////////////////////////////////////
  /// \brief clearing of the render target
  ///
  /// \param color the color will be used to fill the screen
  ////////////////////////////////////////////////////////////
  void clear(const sf::Color& color = {0,0,0});
  ////////////////////////////////////////////////////////////
  /// \brief display to the target
  ////////////////////////////////////////////////////////////
  void display();
  ////////////////////////////////////////////////////////////
  /// \brief Get a read-only reference to the target texture
  ///
  /// After drawing to the render-texture and calling Display,
  /// you can retrieve the updated texture using this function,
  /// and draw it using a sprite (for example).
  /// The internal `sf::Texture` of a render-texture is always the
  /// same instance, so that it is possible to call this function
  /// once and keep a reference to the texture even after it is
  /// modified.
  ///
  /// \return Const reference to the texture
  ///
  ////////////////////////////////////////////////////////////
  [[nodiscard]] const sf::Texture& getTexture() const;

  [[nodiscard]] const sf::Vector2f& getSize() const;


  ////////////////////////////////////////////////////////////
  /// \brief render the current content of the viewport to a render target
  ///
  /// \param renderer the
  ///
  ////////////////////////////////////////////////////////////
  template <typename RenderTarget>
  void render(Renderer<RenderTarget>& renderer) {
    renderer.draw(target, view);
  }

};

}; // namespace MEU

