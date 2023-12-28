#include "gfx/base/Pixel.hpp"
#include "gfx/base/Image.hpp"
#include "rflt/rflt.hpp"

int main()
{
    using namespace gfx;
    using namespace gfx::base;
    using namespace gfx::literals;

    pix p{ 122, 33, 24 };
    std::cout << rflt::to_string(p) << "\n";
    std::cout << p << "\n";

    pix cpy{ std::move(p) };
    std::cout << std::hex << cpy << "\n";

    std::cout << static_cast<unsigned int>(cpy) << "\n";
    auto t = rflt::tupify(p);
    std::get<0>(t) = -12;
    std::cout << std::dec << p << "\n";

    img picture{ 500u, 500u, 0xffffff_rgb };
    save_image(picture, "img/TEST.png");
    picture.fill(0xff00ff_rgb);
    save_image(picture, "img/TEST2.png");
}