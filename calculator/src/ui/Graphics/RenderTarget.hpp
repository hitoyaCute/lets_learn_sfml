#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "Color.hpp"

namespace Calc {
namespace Graphics {

class RenderTarget {
public:// public stuff
    friend class Drawable;
    friend class RenderWindow;
    friend class InteractableElement;

    // RenderTarget(const sf::Vector2i& size):pickingWindow{static_cast<sf::Vector2u>(size)}{}

    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \arg drawable Object to draw (using custom Drawable interface)
    /// \arg states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(class Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) = 0;
    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \arg drawable Object to draw
    /// \arg states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) = 0;
    ////////////////////////////////////////////////////////////
    /// \brief Draw a InteractableElement object to the render target
    /// and picking window, it also performs a picking lists add
    ///
    /// \param drawable Object to draw
    /// \param states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(class InteractableElement& drawable, const sf::RenderStates& states = sf::RenderStates::Default) = 0;

    ////////////////////////////////////////////////////////////
    /// \update the content of the render target
    ////////////////////////////////////////////////////////////
    virtual void display() = 0;

    ////////////////////////////////////////////////////////////
    /// \brief clear of the screen and callback buffer
    ///
    /// \param col the color will be used to flush the screen
    ////////////////////////////////////////////////////////////
    virtual void clear(const Color& col = sf::Color::Black) = 0;

    ////////////////////////////////////////////////////////////
    /// \clear all interactable elements on the buffer
    ////////////////////////////////////////////////////////////
    virtual void clear_elembuf() = 0;
    
    ////////////////////////////////////////////////////////////
    /// \brief adding of new callback
    ///
    /// 
    ////////////////////////////////////////////////////////////
    virtual void add_elemref(class InteractableElement& elem) = 0;

    ////////////////////////////////////////////////////////////
    /// \fetch the element under the cursor
    ///
    /// \param cur the position of the cursor
    ////////////////////////////////////////////////////////////
    virtual class InteractableElement* get_elem_under(const sf::Vector2i& cur) = 0;
    ////////////////////////////////////////////////////////////
    /// \brief fetching of element on the elements lists
    ///
    /// \param id of the the element
    ///
    ////////////////////////////////////////////////////////////
    virtual inline class InteractableElement* fetch_element(const Color& id) = 0;
    ////////////////////////////////////////////////////////////
    /// \brief fetch of pixel on the picking window
    ///
    /// \param pos the pixel coordinates on where to get the pixel
    ///
    ////////////////////////////////////////////////////////////
    virtual const Color getPixel(const sf::Vector2i& pos) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief draw of object to the picking window and add the object
    /// to the elements
    ////////////////////////////////////////////////////////////
    inline void draw_bound(const sf::Drawable& obj) {
        pickingWindow.draw(obj);
    };
    ~RenderTarget() = default;
private: // private stuff
    

    
    // buffer to interaction handler for elements drawn on the screen
    // the key is just the lower 32 bit (Color type) of the the element
    std::unordered_map<Calc::Graphics::Color, class InteractableElement*> elements;

    // buffer on which the object's id would be drawn
    sf::RenderTexture pickingWindow;
 
}; // class RenderTarget

}; // namespace Graphics
}; // namespace Calc

