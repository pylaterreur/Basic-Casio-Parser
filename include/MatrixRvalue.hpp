
#ifndef MATRIXRVALUE_HPP_
# define MATRIXRVALUE_HPP_

#include <iosfwd>

struct MatrixRvalue
{};

std::ostream &operator<<(std::ostream& o, const MatrixRvalue&)
{
  o << "MatrixRvalue" << std::endl;
  return (o);
}

#endif	// !MATRIXRVALUE_HPP_
