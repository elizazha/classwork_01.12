#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>
namespace top{
  struct p_t{
    int x, y;
  };\
  bool operator==(p_t, p_t );
  bool operator!=(p_t, p_t);

  struct frame_t{ //f_t
    p_t aa; // left_bot;
    p_t bb; //right_bot;
  };
  size_t rows(frame_t fr);
  size_t cols(frame_t fr);
  frame_t build_frame(const p_t* ps, size_t s);
}
#endif
