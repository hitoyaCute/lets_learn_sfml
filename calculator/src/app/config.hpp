#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/ContextSettings.hpp>

namespace conf {

static const char* const project_name = "Calculator";
static sf::Vector2u constexpr window_size = {491,511};
static sf::Vector2f constexpr window_size_f {window_size};

static sf::Color const bg = {84, 8, 99};
static sf::Color const button_bg = {146, 72, 122};
static sf::Color const button_fg = {255, 211, 213};
static sf::Font  const button_font {RES_DIR"/fonts/NerdFonts/HackNerdFont-Regular.ttf"};




}; // namespace conf






