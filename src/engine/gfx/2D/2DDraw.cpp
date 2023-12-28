#include "gfx/2D/Draw.hpp"

#include <algorithm>

namespace gfx::GFX2D {

    namespace _details 
    {

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

    void draw_triangle_wireframe(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel)
    {
        draw_line(image, static_cast<ivec2>(v0), static_cast<ivec2>(v1), pixel);
        draw_line(image, static_cast<ivec2>(v1), static_cast<ivec2>(v2), pixel);
        draw_line(image, static_cast<ivec2>(v0), static_cast<ivec2>(v2), pixel);
        return;
    }

    void draw_triangle_antialias_wireframe(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel)
    {
        draw_antialias_line(image, static_cast<ivec2>(v0), static_cast<ivec2>(v1), pixel);
        draw_antialias_line(image, static_cast<ivec2>(v1), static_cast<ivec2>(v2), pixel);
        draw_antialias_line(image, static_cast<ivec2>(v0), static_cast<ivec2>(v2), pixel);
    }

    void draw_triangle_filled(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel)
    {
        _details::frame_vector(image, v0);
        _details::frame_vector(image, v1);
        _details::frame_vector(image, v2); 

        // v0 < v1 < v2
        if (v1.y() < v0.y()) std::swap(v1, v0);
        if (v2.y() < v0.y()) std::swap(v2, v0);
        if (v2.y() < v1.y()) std::swap(v2, v1); 

        double dx0, dx1, temp, xbegin, xend;
        dx0 = (v2.x() - v0.x()) / (v2.y() - v0.y() + 0.1);
        dx1 = (v1.x() - v0.x()) / (v1.y() - v0.y() + 0.1);
        temp = (v2.x() - v1.x()) / (v2.y() - v1.y() + 0.1);

        xbegin = v0.x();
        xend = v0.x();

        for (unsigned y = static_cast<unsigned>(v0.y()); y <= static_cast<unsigned>(v2.y()); ++y, xbegin += dx0, xend += dx1)
        {
            if (y == static_cast<unsigned>(v1.y()))
            {
                dx1 = temp;
                xend = v1.x();
            }
            auto [xmin, xmax] = std::minmax(xbegin, xend);
            for (unsigned x = static_cast<unsigned>(xmin); x < static_cast<unsigned>(xmax); ++x)
            {
                image.set(x, y, pixel);
            }
        }
    }

}