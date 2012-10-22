
#ifndef NUMERICRVALUE_HPP_
# define NUMERICRVALUE_HPP_

#include <iosfwd>

struct NumericRvalue
{};

std::ostream &operator<<(std::ostream& o, const NumericRvalue&)
{
  o << "NumericRvalue" << std::endl;
  return (o);
}

#endif	// !NUMERICRVALUE_HPP_
