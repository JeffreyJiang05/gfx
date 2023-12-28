#include "gfx/base/Pixel.hpp"

namespace gfx {

    namespace base {

        template<>
        std::ostream& operator<<(std::ostream& out, const pixel<unsigned char>& p)
        {
            if (out.flags() & std::ios::ios_base::hex)
                return std::cout << static_cast<unsigned int>(p.red) 
                                << static_cast<unsigned int>(p.green) 
                                << static_cast<unsigned int>(p.blue);
            return std::cout << "(" << 
                static_cast<unsigned int>(p.red) << "," << 
                static_cast<unsigned int>(p.green) << "," << 
                static_cast<unsigned int>(p.blue) << ")";
        }

    }

    RandomPixelGenerator::RandomPixelGenerator() : 
        rd{ std::random_device() }, 
        seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() },
        rng{ seq },
        distrib{ 0, 255 } {}

    RandomPixelGenerator& RandomPixelGenerator::instance()
    {
        static RandomPixelGenerator gen;
        return gen;
    }

    pix RandomPixelGenerator::generate()
    {
        static RandomPixelGenerator gen;
        return pix{ 
            static_cast<unsigned char>(distrib(rng)), 
            static_cast<unsigned char>(distrib(rng)),
            static_cast<unsigned char>(distrib(rng)) 
        };
    }

    namespace literals {

        pix operator""_rgb(unsigned long long rgb_value)
        {
            return pix{ 
                static_cast<unsigned char>((rgb_value & 0xFF0000) >> 16),
                static_cast<unsigned char>((rgb_value & 0x00FF00) >> 8),
                static_cast<unsigned char>(rgb_value & 0x0000FF) 
            };
        }

    }
    
}