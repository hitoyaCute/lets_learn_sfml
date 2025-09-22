#pragma once
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
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

template<typename RenderTarget>
struct Renderer {
private:
  RenderTarget target;
  sf::RenderTexture pickingBuffer;
public:
  Renderer(sf::Vector2u size, std::string title = "SFML Project", sf::State state = sf::State::Windowed);
  ////////////////////////////////////////////////////////////
  /// \render target for textures
  ///
  ////////////////////////////////////////////////////////////
  Renderer(sf::Vector2u size);
  ////////////////////////////////////////////////////////////
  /// \brief Update the contents of the target texture
  ///
  /// This function updates the target texture with what
  /// has been drawn so far. Like for windows, calling this
  /// function is mandatory at the end of rendering. Not calling
  /// it may leave the texture in an undefined state.
  ///
  ////////////////////////////////////////////////////////////
  void display(){
    target.display();
    pickingBuffer.display();
  } 
  ////////////////////////////////////////////////////////////
  /// \brief Clear the entire target with a single color
  ///
  /// This function is usually called once every frame,
  /// to clear the previous contents of the target.
  ///
  /// \param color Fill color to use to clear the render target
  ///
  ////////////////////////////////////////////////////////////
  void clear(sf::Color color = sf::Color::Black) {
    target.clear(color);
    pickingBuffer.clear(sf::Color::Black);
  }

  ////////////////////////////////////////////////////////////
  /// \brief Draw a drawable object to the render target
  ///
  /// \param drawable Object to draw
  /// \param states   Render states to use for drawing
  ///
  ////////////////////////////////////////////////////////////
  void draw(const Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) {
    target.draw(*drawable.object, states);
  }

  ////////////////////////////////////////////////////////////
  /// \brief Draw a interactable object to the picking buffer and render target
  ///
  /// \param drawable Object to draw
  /// \param states   Render states to use for drawing on render target
  ///
  ////////////////////////////////////////////////////////////
  void ObjDraw(const Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) {
    if (drawable.objBound == nullptr or drawable.object == nullptr) {
      throw std::runtime_error("uhhh you missed the part where you reject to give pointer to a object at Renderer::ObjDraw(const Drawable&, const sf::RenderStates)");
    }
    target.draw(*drawable.object, states);
    pickingBuffer.draw(*drawable.objBound);
  }
  ////////////////////////////////////////////////////////////
  /// \brief fetching of item under the cursor
  /// \param ObjectLists   lists of interactable item displyed on screen where its ID was its index
  /// \param mousePos      the curent position of the mouse relative to the render target's position
  ////////////////////////////////////////////////////////////
  Drawable* getItem(std::unordered_map<size_t, Drawable*>& ObjectLists, sf::Vector2i mousePos) {
    // check if the curser was out-bound/outside the render target
    if (mousePos.x < 0 || mousePos.y < 0 ||
        mousePos.x >= (int)target.getSize().x ||
        mousePos.y >= (int)target.getSize().y)
          return nullptr;
    const auto image = pickingBuffer.getTexture().copyToImage();
    
    const sf::Color match = image.getPixel({(uint32_t)mousePos.x, (uint32_t)mousePos.y});
    // color hashing
    const size_t match_id = (match.r << 16) | (match.g << 8) | match.b;
  
    Drawable* output = ObjectLists[match_id];
  
    return output;
  }
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
  void setView(const sf::View& view) {
    target.setView(view);
    pickingBuffer.setView(view);
  }

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

constexpr sf::VertexArray sfShapeToVertexArray(const sf::Shape& shape, size_t size, sf::Color fill_color = sf::Color(0,0,0));

constexpr void apply_texture(sf::VertexArray& arr,
                             const uint32_t vertex_ammount,
                             const sf::Vector2f texture_size) {
  //////////////////////////////////////////////////////////////
  sf::Vector2f arr_size = arr.getBounds().size;

  for (uint8_t j{0}; j < vertex_ammount; j++) {
    sf::Vector2f current_vertex_pos = arr[j].position;
    float ratio_x = current_vertex_pos.x / arr_size.x; // the ammounf of the vertex.x is placed before reaching the size.x
    float ratio_y = current_vertex_pos.y / arr_size.y; // the ammounf of the vertex.y is placed before reaching the size.y
    arr[j].texCoords = {ratio_x * texture_size.x, ratio_y * texture_size.y};
  }
}

}; // namespace MEU
