#include <iostream>
namespace top{

  struct p_t{
    int x, y;
  };

  struct IDraw{
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y; // оператор туда-сюда(space shift(?))
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a==b);
  }

  struct Dot : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    explicit Dot(p_t dd);
    Dot(int x, int y);
  };

  struct frame_t{ //f_t
    p_t aa; // left_bot;
    p_t bb; //right_bot;
  };

  size_t rows(frame_t fr);
  size_t cols(frame_t fr);

  void make_f(IDraw** b, size_t k);
  size_t get_points(const IDraw& d, p_t** pts, size_t& s);
  frame_t build_frame(const p_t* ps, size_t s);
  char* build_canvas(frame_t f, char fill);
  void paint_canvas(char* cnv, frame_t fr, p_t p, char fill); //берем канву,рамку, все точки и кол-во точек и символ, которым заполняем
  void print_canvas(std::ostream& os, const char* cnv, frame_t fr);
  void extend(p_t** pts, size_t s, p_t p);

  struct VSeg
  {
    int x;
    int bot_y;
    int top_y;
  };

  struct HSeg
  {
    int y;
    int left_x;
    int right_x;
  };

  
}

void top::extend(p_t** pts, size_t s, p_t p)
{
    p_t* res = new p_t[s+1];
    for (size_t i = 0; i < s; i++)
    {
        res[i] = (*pts)[i];
    }
    res[s] = p;
    delete[] * pts;
    *pts = res;
}

size_t top::get_points(const IDraw& d, p_t** pts, size_t& s) {
    p_t p = d.begin();
    // добавить массив в начало
    extend(pts, s, p);
    size_t delta = 1;
    p_t next_p = d.next(p);
    while (next_p != d.begin()) {
        extend(pts, s + delta, next_p);
        ++delta;
        //р добавить в массив
        p = next_p;
        next_p = d.next(p);
    }
    s += delta;
    return delta;
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

size_t top::rows(frame_t fr)
{
    return (fr.bb.y - fr.aa.y + 1);
}

size_t top::cols(frame_t fr)
{
    return (fr.bb.x - fr.aa.x + 1);
}

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

top::Dot::Dot(int x, int y) :
    IDraw(),
    o{x, y}
{}

top::Dot::Dot(p_t dd):
  IDraw(),
  o{dd}
{}

  top::p_t top::Dot::begin() const {
  return o;
}

top::p_t top::Dot::next(p_t) const {
  return begin();
}

void top::make_f(IDraw** b, size_t k) {
    b[0] = new Dot(0, 0);
    b[1] = new Dot(1, 1);
    b[2] = new Dot(2, 2);
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
    cnv = build_canvas(fr, '*');
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