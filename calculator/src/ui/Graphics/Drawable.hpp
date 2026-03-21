#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Calc {
namespace Graphics {

class Drawable {
protected:
    // each Drawable should have its own internal data that holds the things to be drawn
    ////////////////////////////////////////////////////////////
    /// \brief Draw the object to a render target
    ///
    /// This is a pure virtual function that has to be implemented
    /// by the derived class to define how the drawable should be
    /// drawn.
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderWindow& window, const sf::RenderStates& states = sf::RenderStates::Default) = 0;
public:// public stuff
    friend class RenderTarget;
    friend class RenderWindow;
}; // class Drawable

}; // namespace Graphics
}; // namespace Calc
