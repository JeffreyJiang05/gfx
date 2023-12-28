#include "gfx/base/Image.hpp"

#include "lib/stb_image_write.h"

#include <iostream>

namespace gfx
{

    void save_image(const img& im, std::string fn)
    {
        stbi_write_png(fn.c_str(), 
            static_cast<int>(im.width()), 
            static_cast<int>(im.height()),
            3,
            (void*) im.data().get(),
            sizeof(img::pix) * im.width());
    }

}