#pragma once

#include <functional>

using shape_func = std::function<uint8_t(int, int)>;

shape_func make_ripple(int, int);
shape_func make_point(int, int);
shape_func make_circle(int, int, int);
