#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iosfwd>
#include "geom.hpp"
namespace top{
  char* build_canvas(frame_t f, char fill);
  void paint_canvas(char* cnv, frame_t fr, p_t p, char fill); //берем канву,рамку, все точки и кол-во точек и символ, которым заполняем
  void print_canvas(std::ostream& os, const char* cnv, frame_t fr);
}
#endif