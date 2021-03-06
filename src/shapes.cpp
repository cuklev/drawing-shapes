#include "shapes.hpp"
#include <cmath>

shape_func make_ripple(int x, int y) {
	return [=](int _x, int _y) -> uint8_t {
		_x -= x; _y -= y;
		return -std::sqrt(_x * _x + _y * _y);
	};
}

shape_func make_point(int x, int y) {
	return [=](int _x, int _y) -> uint8_t {
		_x -= x; _y -= y;
		auto r = 128 - std::sqrt(_x * _x + _y * _y);
		return r < 0 ? 0 : r * 2;
	};
}

shape_func make_circle(int x, int y, int radius) {
	return [=](int _x, int _y) -> uint8_t {
		_x -= x; _y -= y;
		auto dist = radius - std::sqrt(_x * _x + _y * _y);
		return 255 / std::sqrt(std::abs(dist));
	};
}
