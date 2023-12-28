#include <iostream>
#include <random>
#include <chrono>

#include "gfx/2D/Draw.hpp"

#define ITERATIONS 1 << 26
#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 500

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;

    std::random_device rd;
    std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 rand{ seed };
    std::uniform_int_distribution<> dist{ 0, 500 };

    img image{ IMAGE_WIDTH, IMAGE_HEIGHT, 0x000000_rgb };

    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        draw_line(image, ivec2{ dist(rand), dist(rand) }, ivec2{ dist(rand), dist(rand) }, 0xffffff_rgb);
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << " ms" << "\n";

    save_image(image, "img/PerfTest.png");
}