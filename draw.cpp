#include<random>
#include<cmath>

#include<png++/png.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int CIRCLE_COUNT = 64;
const int CIRCLE_RADIUS = 512;

struct Circle {
	int x, y;
} circles[CIRCLE_COUNT];

void draw(png::image<png::rgb_pixel>& output, const Circle& c)
{
	for(png::uint_32 y = 0; y < output.get_height(); ++y)
	{
		for(png::uint_32 x = 0; x < output.get_width(); ++x)
		{
			auto _x = x - c.x;
			auto _y = y - c.y;
			double dist = sqrt(_x * _x + _y * _y);

			dist -= CIRCLE_RADIUS;
			if(dist < 0) dist = -dist;

			int curr = 255 / sqrt(dist + 1);

			// think of other colors
			output[y][x].blue += curr;
		}
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "Give file name\n";
		return 1;
	}

	std::mt19937_64 rng {std::random_device{}()};
	std::uniform_int_distribution<> width_dist(-CIRCLE_RADIUS, WIDTH + CIRCLE_RADIUS);
	std::uniform_int_distribution<> height_dist(-CIRCLE_RADIUS, HEIGHT + CIRCLE_RADIUS);

	for(auto &c : circles)
	{
		c.x = width_dist(rng);
		c.y = height_dist(rng);
	}

	png::image<png::rgb_pixel> output(WIDTH, HEIGHT);

	for(int i = 0; i < CIRCLE_COUNT; ++i)
	{
		std::cout << "Drawing Circle " << i + 1 << " / " << CIRCLE_COUNT << '\n';
		draw(output, circles[i]);
	}

	output.write(argv[1]);
}
