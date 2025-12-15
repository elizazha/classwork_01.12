#ifndef IDRAW_HPP
#define IDRAW_HPP
#include <cstddef>
#include "geom.hpp"
namespace top{
  struct IDraw{
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };
  size_t get_points(const IDraw& d, p_t** pts, size_t& s);
}
#endif