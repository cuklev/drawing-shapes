#pragma once

#include <functional>

std::function<uint8_t(int, int)> make_ripple(int, int);
std::function<uint8_t(int, int)> make_point(int, int);
std::function<uint8_t(int, int)> make_circle(int, int, int);
