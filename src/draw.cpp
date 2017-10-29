#include "shapes.hpp"
#include <random>
#include <png++/png.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int CIRCLE_RADIUS = 512;
const int CIRCLE_COUNT = 64;

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << "Give file name\n";
		return 1;
	}

	std::mt19937_64 rng {std::random_device{}()};
	std::uniform_int_distribution<> width_dist(-CIRCLE_RADIUS, WIDTH + CIRCLE_RADIUS);
	std::uniform_int_distribution<> height_dist(-CIRCLE_RADIUS, HEIGHT + CIRCLE_RADIUS);

	//	auto r = make_ripple(200, 400);
	//	auto p = make_point(300, 300);
	//	auto c = make_circle(900, 600, 512);

	std::vector<shape_func> shapes(CIRCLE_COUNT);
	for(auto& s: shapes)
		s = make_circle(width_dist(rng), height_dist(rng), CIRCLE_RADIUS);

	png::image<png::rgb_pixel> output(WIDTH, HEIGHT);

	for(png::uint_32 y = 0; y < output.get_height(); ++y) {
		for(png::uint_32 x = 0; x < output.get_width(); ++x) {
			for(auto& s: shapes) {
				auto result = s(x, y);
				//output[y][x].blue -= result;
				output[y][x].green += result;
				//output[y][x].red += result;
			}
		}
	}

	output.write(argv[1]);
}
