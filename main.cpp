#include <iostream>
#include <stdexept>
#include <algorithm>
#include "ascii_draw"
namespace top{
  size_t rows(frame_t fr);
  size_t cols(frame_t fr);

  void make_f(IDraw** b, size_t k);
  void extend(p_t** pts, size_t s, p_t p);

  struct Vseg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    int x;
    int y1, y2;
    Vseg(int xx, int yy1, int yy2);
  };

  struct Hseg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    int y;
    int x1, x2;
    Hseg(int yy, int xx1, int xx2);
  };

  struct Seg_45 : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t bot;
    p_t top;
    Seg_45(int xbot, int ybot, int xtop, int ytop);
  };

  struct Square: IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    int x, y, side;
    Square(int x1, int y2, int a);

  };

  struct Rectangle: IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    int x, y, horside, vertside;
    Rectangle(int x1, int y1, int horside1, int vertside1);
  };
  
}

top::Rectangle::Rectangle(int x1, int y1, int horside1, int vertside1):
  x{x1}, y{y1}, horside{horside1}, vertside{vertside1}
  {}

top::p_t top::Rectangle::begin() const
{
  return p_t{x, y};
}

top::p_t top::Rectangle::next(p_t current) const
{
  int right_x = x + horside -1;
  int top_y = y + vertside -1;
  if (current.x < right_x && current.y == y)
  {
    return p_t{current.x + 1, y};
  }
  else if (current.x == right_x && current.y < top_y)
  {
    return p_t{right_x, current.y + 1};
  }
  else if (current.x > x && current.y == top_y)
  {
    return p_t{current.x - 1, top_y};
  }
  else if(current.x == x && current.y > y)
  {
    return p_t{x, current.y - 1};
  }
  return begin();
}


top::Square::Square(int x1, int y2, int a):
  x{x1}, y{y2}, side{a}
  {}

top::p_t top::Square::begin() const
{
  return p_t{x, y};
}

top::p_t top::Square::next(p_t current) const
{
  int right_x = x + side - 1;
  int top_y = y + side - 1;
  if (current.x < right_x && current.y == y)
  {
    return p_t{current.x+1, y};
  }
  else if ( current.x == right_x && current.y < top_y)
  {
    return p_t{right_x, current.y + 1};
  }
  else if (current.y == top_y && current.x > x)
  {
    return p_t{current.x - 1, top_y};
  }
  else if ( current.x == x && current.y > y)
  {
    return p_t{x, current.y - 1};
  }
  return begin();
}

top::Vseg::Vseg(int xx, int yy1, int yy2):
  x{xx}, y1{yy1}, y2{yy2}
{}

top::p_t top::Vseg::begin() const
{
  return p_t{x, std::min(y1, y2)};
}

top::p_t top::Vseg::next(p_t current) const
{
  int maxy = std::max(y1, y2);
  if (current.y < maxy) {
      return p_t{x, current.y + 1};
  }
  return begin();
}


top::Hseg::Hseg(int yy, int xx1, int xx2):
  y{yy}, x1{xx1}, x2{xx2}
{}
top::p_t top::Hseg::begin() const
{
  return p_t{std::min(x1, x2), y};
}

top::p_t top::Hseg::next(p_t current) const
{
  int maxx = std::max(x1, x2);
  if (current.x < maxx)
  {
    return p_t{current.x + 1, y};
  }
  return begin();
}


top::Seg_45::Seg_45(int xbot, int ybot, int xtop, int ytop):
  bot{xbot, ybot}, top{xtop, ytop}
{
  int left_x = std::min(xbot, xtop);
  int right_x = std::max(xbot, xtop);
  int bottom_y = std::min(ybot, ytop);
  int top_y = std::max(ybot, ytop);
  
  bot = p_t{left_x, bottom_y};
  top = p_t{right_x, top_y};
}

top::p_t top::Seg_45::begin() const
{
  return bot;
}

top::p_t top::Seg_45::next(p_t current) const
{
  if (current.x < top.x && current.y < top.y)
  {
    return p_t {current.x + 1, current.y + 1};
  }
  return begin();
}

// void top::make_f(IDraw** b, size_t k) {
//     b[0] = new Dot(0, 0);
//     b[1] = new Dot(1, 1);
//     b[2] = new Dot(2, 2);
// }
//
// void top::make_f(IDraw** b, size_t k) {
//     if (k >= 1) b[0] = new Vseg(2, 0, 4);
//     if (k >= 2) b[1] = new Hseg(2, 0, 4);
//     if (k >= 3) b[2] = new Seg_45(0, 0, 4, 4);
// }
void top::make_f(IDraw** b, size_t k) {
    if (k >= 1) b[0] = new Square(1, 1, 5);
    if (k >= 2) b[1] = new Rectangle(8, 2, 6, 4);
    if (k >= 3) b[2] = new Seg_45(1, 8, 5, 12);
}

int main()
{
  using namespace top;
  IDraw* f[3] = {};
  p_t* p = nullptr;
  char* cnv = nullptr;
  size_t s = 0;
  int err = 0;
  try{
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(*(f[i]), &p, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr, '_');
    for (size_t i = 0; i < s; ++i)
    {
      paint_canvas(cnv, fr, p[i], '.');
    }
    print_canvas(std::cout, cnv, fr);
  }
  catch(...)
  {
    err = 1;
  }
  delete f[0]; delete f[1]; delete f[2];
  delete[] p;
  delete[] cnv;
  return err;
}
// h/w before 12.10 - struct VSeg and struct HSeg and line under 45 degrees;
// h/w before 12.13 - struct square and struct rectangle;