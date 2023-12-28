#include "gfx/2D/Draw.hpp"

namespace gfx::GFX2D {

    namespace _details
    {
        constexpr static inline unsigned int X = 0;
        constexpr static inline unsigned int Y = 1;

        void frame_vector(const img& img, ivec2& data)
        {
            data[X] += (img.width() >> 1);
            data[Y] = (img.height() >> 1) - data[Y];
        }

        void draw_line_octant_I(img& img, ivec2& p0, ivec2& p1, int A, int B, const img::pix& pixel)
        {
            int dist = (A << 1) + B;
            while (p0[X] <= p1[X])
            {
                img.set(p0[X], p0[Y], pixel);
                if (dist > 0)
                {
                    ++p0[Y];
                    dist += (B << 1);
                }
                ++p0[X];
                dist += (A << 1);
            }
        }

        void draw_line_octant_II(img& img, ivec2& p0, ivec2& p1, int A, int B, const img::pix& pixel)
        {
            int dist = (B << 1) + A;
            while (p0[Y] <= p1[Y])
            {
                img.set(p0[X], p0[Y], pixel);
                if (dist < 0)
                {
                    ++p0[X];
                    dist += (A << 1);
                }
                ++p0[Y];
                dist += (B << 1);
            }
        }

        void draw_line_octant_VII(img& img, ivec2& p0, ivec2& p1, int A, int B, const img::pix& pixel)
        {
            int dist = A - (B << 1);
            while (p0[Y] >= p1[Y])
            {
                img.set(p0[X], p0[Y], pixel);
                if (dist > 0)
                {
                    ++p0[X];
                    dist += (A << 1);
                }
                --p0[Y];
                dist -= (B << 1);
            }
        }

        void draw_line_octant_VIII(img& img, ivec2& p0, ivec2& p1, int A, int B, const img::pix& pixel)
        {
            int dist = (A << 1) - B;
            while (p0[X] <= p1[X])
            {
                img.set(p0[X], p0[Y], pixel);
                if (dist < 0)
                {
                    --p0[Y];
                    dist -= (B << 1);
                }
                ++p0[X];
                dist += (A << 1);
            }
        }

        double fpart(double value)
        {
            return value - (int) value;
        }

        double rfpart(double value)
        {
            return 1 - fpart(value);
        }

        gfx::pix apply_brightness(double brightness, const pix& pixel, const pix& background)
        {
            return lerp(background, pixel, brightness);
        }

    }

    void draw_line(img& image, ivec2 p0, ivec2 p1, img::pix pixel)
    {
        _details::frame_vector(image, p0);
        _details::frame_vector(image, p1);

        if (p1.x() < p0.x()) std::swap(p0,p1);
        int B = p0.x() - p1.x();
        int A = p1.y() - p0.y();
        if (A >= 0)
        {
            if (A <= -B)    _details::draw_line_octant_I(image, p0, p1, A, B, pixel);
            else            _details::draw_line_octant_II(image, p0, p1, A, B, pixel);
        }
        else
        {
            if (A >= B)     _details::draw_line_octant_VIII(image, p0, p1, A, B, pixel); 
            else            _details::draw_line_octant_VII(image, p0, p1, A, B, pixel);
        }
    }  

    void draw_antialias_line(img& img, ivec2 p0, ivec2 p1, img::pix pixel)
    {
        _details::frame_vector(img, p0);
        _details::frame_vector(img, p1);

        bool steep = abs(p1.y() - p0.y()) > abs(p1.x() - p0.x());
        if (steep) // Swap x, y values if steep
        {
            std::swap(p0[0], p0[1]);
            std::swap(p1[0], p1[1]);
        }

        if (p0.x() > p1.x()) std::swap(p0, p1);
        ivec2 delta = p1 - p0;

        double gradient, intery;

        if (!delta.x()) gradient = 1.0;
        else            gradient = (double) delta.y() / delta.x();

        intery = p0.y() + gradient;

        if (steep)
        {
            img.set(p0.y(), p0.x(), _details::apply_brightness(0.5, pixel, img.at(p0.y(), p0.x())));
            img.set(p1.y(), p1.x(), _details::apply_brightness(0.5, pixel, img.at(p1.y(), p1.x())));

            for (int x = p0.x() + 1; x < p1.x(); ++x, intery += gradient)
            {
                img.set((unsigned) intery, x, 
                    _details::apply_brightness(_details::rfpart(intery), pixel, img.at((int) intery, x)));
                img.set((unsigned) intery + 1, x, 
                    _details::apply_brightness(_details::fpart(intery), pixel, img.at((int) intery + 1, x)));
            }
        }
        else
        {
            img.set(p0.x(), p0.y(), _details::apply_brightness(0.5, pixel, img.at(p0.x(), p0.y())));
            img.set(p1.x(), p1.y(), _details::apply_brightness(0.5, pixel, img.at(p1.x(), p1.y())));

            for (int x = p0.x() + 1; x < p1.x(); ++x, intery += gradient)
            {
                img.set(x, (unsigned) intery, 
                    _details::apply_brightness(_details::rfpart(intery), pixel, img.at(x, (int) intery)));
                img.set(x, (unsigned) intery + 1, 
                    _details::apply_brightness(_details::fpart(intery), pixel, img.at(x, (int) intery + 1)));
            }
        }
    }
}