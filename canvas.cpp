#include "canvas.hpp"
#include <iostream>
char* top::build_canvas(frame_t fr, char fill)
{
    char* cnv = new char[rows(fr) * cols(fr)];
    for (size_t i = 0; i < rows(fr) * cols(fr); i++)
    {
        cnv[i] = fill;
    }
    return cnv;
}

void top::paint_canvas(char* cnv, frame_t fr, p_t p, char fill)
{
    int dx = p.x - fr.aa.x;
    int dy = fr.bb.y - p.y;
    cnv[dy * cols(fr) + dx] = fill;
}

void top::print_canvas(std::ostream& os, const char* cnv, frame_t fr)
{
    for (size_t i = 0; i < rows(fr); ++i) {
        for (size_t j = 0; j < cols(fr); ++j) {
            os << cnv[i * cols(fr) + j];
        }
        os << "\n";
    }
}