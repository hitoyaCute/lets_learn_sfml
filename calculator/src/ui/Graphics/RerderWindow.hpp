#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "Color.hpp"
#include "RenderTarget.hpp"
#include "Interactable.hpp"

namespace Calc {
namespace Graphics {

class RenderWindow: public RenderTarget {

public:
    friend class InteractableElement;

    RenderWindow() = default;
    RenderWindow(sf::RenderWindow& window); 
    ~RenderWindow() = default;
    auto get_() {
        return elements;
    }
    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \param drawable Object to draw (using custom Drawable interface)
    /// \param states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(Calc::Graphics::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) override;
    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \param drawable Object to draw
    /// \param states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) override;
    ////////////////////////////////////////////////////////////
    /// \brief Draw a InteractableElement object to the render target
    /// and picking window, it also performs a picking lists add
    ///
    /// \param drawable Object to draw
    /// \param states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(InteractableElement& drawable, const sf::RenderStates& states = sf::RenderStates::Default) override;

    ////////////////////////////////////////////////////////////
    /// \brief push of callback function from element
    ///
    /// \param    element a interactables that mutates as you interacts with it
    /// \callback a function that will process the interaction and perform a certain task
    ///\ \ specified by the element
    /// 
    ////////////////////////////////////////////////////////////
    void add_elemref(class InteractableElement& elem) override;
    ////////////////////////////////////////////////////////////
    /// \fetch the element under the cursor
    ///
    /// \param cur the position of the cursor
    ////////////////////////////////////////////////////////////
    [[nodiscard]] class InteractableElement* get_elem_under(const sf::Vector2i& cur) override;

    ////////////////////////////////////////////////////////////
    /// \update the content of the render window and picking window
    ///
    ////////////////////////////////////////////////////////////
    void display() override;
    ////////////////////////////////////////////////////////////
    /// \brief clear of the screen and callback buffer
    ///
    /// \param col the color will be used to flush the screen
    ////////////////////////////////////////////////////////////
    void clear(const Color& col = sf::Color::Black) override;

    ////////////////////////////////////////////////////////////
    /// \clear all interactable elements on the buffer
    ////////////////////////////////////////////////////////////
    void clear_elembuf() override;
private:
public:
    ////////////////////////////////////////////////////////////
    /// \brief fetching of element on the elements lists
    ///
    /// \param id of the the element
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] class InteractableElement* fetch_element(const Color& id) override;
    ////////////////////////////////////////////////////////////
    /// \brief fetch of pixel on the picking window
    ///
    /// \param pos the pixel coordinates on where to get the pixel
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] const Color getPixel(const sf::Vector2i& pos) override;

    sf::RenderWindow* window_ref;
}; // class RenderWindow

}; // namespace Graphics
}; // namespace Calc
