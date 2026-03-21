///////////////////////////////////////////////////////
/// \Button
///
/// a simple primitive button, which user can click and triger some event.
/// the button has customizable appearance, by overriding the draw and callback function
/// the callback function will be automatically called when the user hover to the button
/// and all user event will be passed to the callback, and the button object should handle
/// the event
///
///////////////////////////////////////////////////////

#pragma once

#include <string>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>


#include "../Graphics/states.hpp"
#include "../Graphics/Interactable.hpp"
#include "../Graphics/RenderTarget.hpp"

namespace Calc {
namespace Primitive {

class Button: public Graphics::InteractableElement {
    enum class State {
        normal,
        hovering,
        pressed,
        // short duration pressed
        // something shorter than 
        clicked,
        dragging
    };
    sf::Vector2f bound;
    sf::Vector2f position;
    
    State state = State::normal;
    // state value that can be used on any porpose
    // but we use it here to see if the user is hovering
    // by using it as time sinse last left_down and resseting
    // to zero everytime we left_up, we also use this to
    // checkfor click where 1:10 in second
    int state_raw = 0;

    std::string tag;


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
    void draw(Graphics::RenderTarget& window, const sf::RenderStates& states = sf::RenderStates::Default) override;
    
public:

    Button() = default;
    Button(const std::string& tag);

    ////////////////////////////////////////////////////////////
    /// \brief Callback function to handle interaction events
    ////
    /// This is a pure virtual function that has to be implemented
    /// by the derived class to define how the object should
    /// respond to interaction events.
    //// \param states Current interaction states
    /////////////////////////////////////////////////////////////
    void callback(const Window::Interaction_state& states) override;
    void setBound(const sf::Vector2f& bound, const sf::Vector2f& pos);
}; // class Button

}; // namespace Primitive
}; // namesapce Calc
