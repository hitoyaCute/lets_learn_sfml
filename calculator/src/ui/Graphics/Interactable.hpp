////////////////////////////////////////////////////////////
///
/// \Interactables are types of drawable object that has special functionality
/// this object has special callback function when the cursor is on the scope of the object,
/// and the callback will be executed when a event happened on the scope of the element
///
///////////////////////////////////////////////////////////


#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states.hpp"
#include "RenderTarget.hpp"

namespace Calc {
namespace Graphics {

class InteractableElement{
protected:
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
    virtual void draw(Graphics::RenderTarget& window, const sf::RenderStates& states = sf::RenderStates::Default) = 0;
public:
    // callback is the function will be executed when a event happened on the scope of the element
    virtual void callback(const Window::Interaction_state& state) = 0;
    friend class RenderWindow;
};

}; // namespace Graphics
}; // namespace Calc


