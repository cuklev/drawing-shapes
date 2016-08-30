#include<random>
#include<cmath>

#include<png++/png.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int CIRCLE_COUNT = 256;
const int CIRCLE_RADIUS = 256;

struct circle {
	int x, y;
} circles[CIRCLE_COUNT];

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cout << "Give file name\n";
		return 1;
	}

	std::mt19937_64 rng {std::random_device{}()};
	std::uniform_int_distribution<> width_dist(-CIRCLE_RADIUS, WIDTH - CIRCLE_RADIUS);
	std::uniform_int_distribution<> height_dist(-CIRCLE_RADIUS, HEIGHT - CIRCLE_RADIUS);

	for(auto &c : circles)
	{
		c.x = width_dist(rng);
		c.y = height_dist(rng);
	}

	png::image<png::rgb_pixel> output(WIDTH, HEIGHT);
	for(png::uint_32 y = 0; y < output.get_height(); ++y)
	{
		for(png::uint_32 x = 0; x < output.get_width(); ++x)
		{
			uint8_t r = 0, g = 0, b = 0;
			for(int k = 0; k < CIRCLE_COUNT; ++k)
			{
				auto &c = circles[k];
				double dist = sqrt((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y));
				dist -= CIRCLE_RADIUS;
				if(dist < 0) dist = -dist;
				int curr = std::log(dist) * 10;

				int t = k & 3;
				if(t == 0 || t == 3) r += curr;
				if(t == 1 || t == 3) g += curr;
				if(t == 2 || t == 3) b += curr;
			}

			output[y][x] = {r, g, b};
		}
	}
	output.write(argv[1]);
}

