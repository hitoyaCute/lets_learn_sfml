/*
stuff that manage stuff being drawn on screen



 */

#include <cstddef>
#include <functional>
#include <unordered_map>
#include <SFML/Window/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>



namespace MEU {


struct UserState {
  enum State {
    Hovering,
    Dragging,
    Clicked,
    
  };
  State interact_mode = Hovering;
};


struct Drawable {
  sf::VertexArray* object;
  sf::VertexArray* objBound;
  const size_t size;
  sf::Color id;
  sf::Vector2f position;
  void setPosition(sf::Vector2f pos);
  void setFillColor(sf::Color col);
  Drawable(sf::VertexArray& arr, size_t size_, sf::Color id_, sf::Vector2f pos);
  Drawable(sf::VertexArray& arr, size_t size_, sf::Vector2f pos);

  std::function<void(Drawable self, const UserState& button)>* interact;
};

struct Renderer {
private:
  sf::RenderWindow target;
  sf::RenderTexture pickingBuffer;
public:
  Renderer(sf::Vector2u size, std::string title = "SFML Project", sf::State state = sf::State::Windowed);
  
  void display();

  ////////////////////////////////////////////////////////////
  /// \brief Clear the entire target with a single color
  ///
  /// This function is usually called once every frame,
  /// to clear the previous contents of the target.
  ///
  /// \param color Fill color to use to clear the render target
  ///
  ////////////////////////////////////////////////////////////
  void clear(sf::Color color = sf::Color::Black);
  ////////////////////////////////////////////////////////////
  /// \brief Draw a drawable object to the render target
  ///
  /// \param drawable Object to draw
  /// \param states   Render states to use for drawing
  ///
  ////////////////////////////////////////////////////////////
  void draw(const Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
  ////////////////////////////////////////////////////////////
  /// \brief Draw a interactable object to the picking buffer and render target
  ///
  /// \param drawable Object to draw
  /// \param states   Render states to use for drawing on render target
  ///
  ////////////////////////////////////////////////////////////
  void ObjDraw(const Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
  ////////////////////////////////////////////////////////////
  /// \brief fetching of item under the cursor
  /// \param ObjectLists   lists of interactable item displyed on screen where its ID was its index
  ////////////////////////////////////////////////////////////
  Drawable* getItem(std::unordered_map<size_t, Drawable*>& ObjectLists);
  ////////////////////////////////////////////////////////////
  /// \brief Limit the framerate to a maximum fixed frequency
  ///
  /// If a limit is set, the window will use a small delay after
  /// each call to `display()` to ensure that the current frame
  /// lasted long enough to match the framerate limit.
  /// SFML will try to match the given limit as much as it can,
  /// but since it internally uses `sf::sleep`, whose precision
  /// depends on the underlying OS, the results may be a little
  /// imprecise as well (for example, you can get 65 FPS when
  /// requesting 60).
  ///
  /// \param limit Framerate limit, in frames per seconds (use 0 to disable limit)
  ///
  ////////////////////////////////////////////////////////////
  void setFramerateLimit(unsigned int fps);

  ////////////////////////////////////////////////////////////
  /// \brief Enable or disable vertical synchronization
  ///
  /// Activating vertical synchronization will limit the number
  /// of frames displayed to the refresh rate of the monitor.
  /// This can avoid some visual artifacts, and limit the framerate
  /// to a good value (but not constant across different computers).
  ///
  /// Vertical synchronization is disabled by default.
  ///
  /// \param enabled `true` to enable v-sync, `false` to deactivate it
  ///
  ////////////////////////////////////////////////////////////
  void setVerticalSyncEnabled(bool enabled);

  bool isOpen();
  
  void close();
  ////////////////////////////////////////////////////////////
  /// \brief Pop the next event from the front of the FIFO event queue, if any, and return it
  ///
  /// This function is not blocking: if there's no pending event then
  /// it will return a `std::nullopt`. Note that more than one event
  /// may be present in the event queue, thus you should always call
  /// this function in a loop to make sure that you process every
  /// pending event.
  /// \code
  /// while (const std::optional event = window.pollEvent())
  /// {
  ///    // process event...
  /// }
  /// \endcode
  ///
  /// \return The event, otherwise `std::nullopt` if no events are pending
  ///
  /// \see `waitEvent`, `handleEvents`
  ///
  ////////////////////////////////////////////////////////////
  [[nodiscard]] std::optional<sf::Event> pollEvent();

  [[nodiscard]] sf::WindowBase& getWindowRef();



};




sf::VertexArray& sfShapeToVertexArray(const sf::Shape& shape, size_t size, sf::Color fill_color = sf::Color(0,0,0));




}; // namespace MEU
//
//





