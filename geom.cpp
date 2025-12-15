#include "geom.hpp"
#includee <stdexept>
bool top::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y; // оператор туда-сюда(space shift(?))
}

bool top::operator!=(p_t a, p_t b)
{
  return !(a==b);
}
size_t top::rows(frame_t fr)
{
    return (fr.bb.y - fr.aa.y + 1);
}

size_t top::cols(frame_t fr)
{
    return (fr.bb.x - fr.aa.x + 1);
}

top::frame_t top::build_frame(const p_t* pts, size_t s)
{
    if (!s)
    {
        throw std::logic_error("bad size");
    }
    int minx = pts[0].x, maxx = minx;
    int miny = pts[0].y, maxy = miny;
    for (size_t i = 0; i < s; i++)
    {
        minx = std::min(minx, pts[i].x);
        miny = std::min(miny, pts[i].y);
        maxx = std::max(maxx, pts[i].x);
        maxy = std::max(maxy, pts[i].y);
    }
    p_t aa{ minx, miny };
    p_t bb{ maxx, maxy };
    return { aa, bb };
}