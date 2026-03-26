#include "app/helpers.hpp"
#include "app/config.hpp"
#include "ui/shapes/basicShape.hpp"

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

[[maybe_unused]] const char* valid_char {
    "0123456789"                         // alpha numerals
    "+-*/"                               // operator chars
    ".,E"                                // special chars thats not just displayed normally
    " "                                  // just blank
};

// needs a fix ammount of digits
inline void update_digit(sf::VertexArray& digit, const sf::Vector2f& pos, const char value) {
    
}

inline void draw_digits(sf::RenderTarget& win, const char*& value, const size_t& len) {
    // sf::VertexArray digit{sf::PrimitiveType::Triangles, idk};
}

// \@brief make stuff
void draw_numdisplay(sf::RenderTarget &win, const std::string &d) {
    static const ulong display_vertex_count = 8 * 4;
    static sf::VertexArray display_vertex{sf::PrimitiveType::TriangleFan, display_vertex_count};
    static const float border_thickness = 0.9;
    static const float border_radius = 23.f;
    static const sf::Vector2f size{406, 75};
    static const sf::Vector2f pos{37, 14};

    // draw border
    Calc::Shape::CreateRoundedRect(
            display_vertex,
            display_vertex_count,
            border_radius + border_thickness,
            {size.x + border_thickness * 2,
             size.y + border_thickness * 2},
            {pos.x - border_thickness,
             pos.y - border_thickness},
            sf::Color::White);
    win.draw(display_vertex);
    // draw display
    Calc::Shape::CreateRoundedRect(
            display_vertex,
            display_vertex_count,
            border_radius,
            size, pos,
            conf::button_bg);
    win.draw(display_vertex);
}

/*
58
|    ###################           |    1111111111111111111     
    #####################              111111111111111111111    
 ##    #######@#######    ##        22    111111141111111    55 
#####/       @@@       \#####      222220       444       h55555
#####//\\   @@@@@   //\\#####      222220033   44444   ffhh55555
#####//\\\  @@@@@  ///\\#####      2222200333  44444  fffhh55555
######/\\\\ @@@@@ ////\######      22222203333 44444 ffffh555555
#######\\\\\@@@@@/////#######      22222223333344444fffff5555555
####### \\\\@@@@@//// #######      2222222 333344444ffff 5555555
######     \ @@@ /     ######      222222     3 444 f     555555
  #     ##### @ ######    #          2     66666 4 777777    5  
     ######### ##########               666666666 7777777777    
  #     ##### @ ######    #          8     66666 a 777777    c  
######     / @@@ \     ######      888888     9 aaa b     cccccc
####### ////@@@@@\\\\ #######      8888888 9999aaaaabbbb ccccccc
#######/////@@@@@\\\\\#######      888888899999aaaaabbbbbccccccc
######\//// @@@@@ \\\\/######      888888d9999 aaaaa bbbbicccccc
#####\\///  @@@@@  \\\//#####      88888dd999  aaaaa  bbbiiccccc
#####\\//   @@@@@   \\//#####      88888dd99   aaaaa   bbiiccccc
#####\       @@@       /#####      88888d       aaa       iccccc
 ##    #######@#######    ##        88    eeeeeeeaeeeeeee    cc 
    #####################              eeeeeeeeeeeeeeeeeeeee    
     ###################                eeeeeeeeeeeeeeeeeee     
1:
 6:59->24:59->25:60->
22:61->15:61->15:60->
14:61-> 8:61-> 5:60
2:
 2:61-> 3:61-> 5:62->
 5:62-> 7:66-> 7:67->
6:68-> 3:69-> 1:68-> 1:62
0:
 6:62-> 7:63-> 7:65-> 6:64
3:
 8:63-> 9:63->12:66->
12:68-> 9:67-> 8:66
4:
15:61->17:63->17:67->
15:69->13:67->13:63
f:
21:63->22:63->22:66->
21:67->18:68->18:66
h:
24:62->24:64->23:65->23:63
5:
27:61->28:61->29:62->
29:68->27:69->24:68->
23:67->23:66->25:64->62:


*/

