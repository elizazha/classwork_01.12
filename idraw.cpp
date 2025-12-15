#include "idraw.hpp"
namespace{
  void top::extend(top::p_t** pts, size_t s, top::p_t p)
  {
      top::p_t* res = new top::p_t[s+1];
      for (size_t i = 0; i < s; i++)
      {
          res[i] = (*pts)[i];
      }
      res[s] = p;
      delete[] * pts;
      *pts = res;
  }
}
size_t top::get_points(const IDraw& d, top::p_t** pts, size_t& s) {
    p_t p = d.begin();
    // добавить массив в начало
    extend(pts, s, p);
    size_t delta = 1;
    top::p_t next_p = d.next(p);
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
