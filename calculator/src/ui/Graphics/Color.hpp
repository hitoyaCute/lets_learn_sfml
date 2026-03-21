#pragma once

#include "util/bound.hpp"
#include <cstdint>
#include <algorithm>
#include <functional>
#include <SFML/Graphics/Color.hpp>

namespace Calc {
namespace Graphics {

struct Color {
    #pragma GCC diagnostic ignored "-Wreorder"
    union {
        struct {
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;
            uint8_t a = 0;
        };
        // uint32_t rgba;
    };

    Color() = default;
    // constexpr Color(const uint32_t _rgba):rgba{_rgba} {}
    // constexpr Color(const void* full):rgba{static_cast<uint32_t>((ulong)full)}{}
    constexpr Color(const void* full) {
        a = 0xff;
        b = (long(full) >> 8) & 0xff;
        g = (long(full) >> 16) & 0xff;
        r = (long(full) >> 24) & 0xff;
    }

    constexpr Color(const sf::Color& col):r{col.r}, g{col.g}, b{col.b}, a{col.a} {}
    constexpr Color(const uint8_t red,const uint8_t green,const uint8_t blue,const uint8_t alpha):
        r{red},g{green},b{blue},a{alpha}{}
    #pragma GCC diagnostic warning "-Wreorder"

    constexpr uint32_t rgba() const {
        return (r << 24) |
               (g << 16) |
               (b << 8) | a;
    }
    constexpr uint32_t rgb() const {
        return (r << 16) |
               (g << 8) | b;
    }
    [[nodiscard]] inline constexpr uint32_t toId() const {
        return (r << 24) |
               (g << 16) |
               (b << 8) | 0xff;
    }
    [[nodiscard]] inline constexpr bool operator==(const Color& B) const {
        return r == B.r and
               g == B.g and
               b == B.b and
               a == B.a;
    }
    [[nodiscard]] inline constexpr bool operator==(const sf::Color& B) const {
        return r == B.r and
               g == B.g and
               b == B.b and
               a == B.a;
    }

    [[nodiscard]] inline constexpr operator sf::Color() const {
        return sf::Color{r,g,b,a};
    }

}; // class Color

[[nodiscard]] inline constexpr Color operator+(const Color& self, const uint8_t& scalar) {
    return{(uint8_t)std::min(self.r + scalar, 255),
           (uint8_t)std::min(self.g + scalar, 255),
           (uint8_t)std::min(self.b + scalar, 255),
           self.a}; 
}

[[nodiscard]] inline constexpr Color operator+(const Color& A, const Color& B) {
    return{(uint8_t)std::min(A.r + B.r, 255),
           (uint8_t)std::min(A.g + B.g, 255),
           (uint8_t)std::min(A.b + B.b, 255),
           A.a
    };
}

[[nodiscard]] inline constexpr Color operator-(const Color& self, const uint8_t& scalar) {
    return{uint8_t(std::max(self.r - scalar, 0)),
           uint8_t(std::max(self.g - scalar, 0)),
           uint8_t(std::max(self.b - scalar, 0)),
           self.a};
}

[[nodiscard]] inline constexpr Color operator*(const Color& self, const float& scalar) {
    return{uint8_t(cUtils::bound(self.r * scalar, 255.f, 0.f)),
           uint8_t(cUtils::bound(self.g * scalar, 255.f, 0.f)),
           uint8_t(cUtils::bound(self.b * scalar, 255.f, 0.f)),
           self.a};
}

[[nodiscard]] inline constexpr Color operator/(const Color& self, const float& scalar) {
    return{uint8_t(cUtils::bound(self.r / scalar, 255.f, 0.f)),
           uint8_t(cUtils::bound(self.g / scalar, 255.f, 0.f)),
           uint8_t(cUtils::bound(self.b / scalar, 255.f, 0.f)),
           self.a};
}

inline void operator+=(Color& self, const int& scalar) {
    self = self + scalar;
}

inline void operator-=(Color& self, const int& scalar) {
    self = self - scalar;
}

[[nodiscard]] inline constexpr Color mixColorSubtractive(const Color& A, const Color& B) {
    Color Atemp;
    Atemp.a = std::max(A.a + B.a - std::min(A.a * B.a, 255) / 255, 0);
    return {
        (Atemp * ((float)Atemp.a / 255.f) + B * ((float)B.a / 255.f)) / (Atemp.a + B.a)
    };
};

[[nodiscard]] inline constexpr Color mixColorBlend(const Color& A, const Color& B) {
    return {
        uint8_t(std::max(A.r + B.r - (std::min(A.r * B.r, 255) / 255), 0)),
        uint8_t(std::max(A.g + B.g - (std::min(A.g * B.g, 255) / 255), 0)),
        uint8_t(std::max(A.b + B.b - (std::min(A.b * B.b, 255) / 255), 0)),
        uint8_t(std::max(A.a + B.a - (std::min(A.a * B.a, 255) / 255), 0))
    };   
}

}; // namespace Graphics
}; // namespace Calc

template <>
struct std::hash<Calc::Graphics::Color> {
    inline constexpr size_t operator()(const Calc::Graphics::Color& col) const {
        return col.toId();
    }
};
