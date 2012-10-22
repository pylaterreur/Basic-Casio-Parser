
#ifndef VOIDEXPRESSION_HPP_
# define VOIDEXPRESSION_HPP_

#include <iosfwd>

struct VoidExpression
{};

std::ostream &operator<<(std::ostream& o, const VoidExpression&)
{
  o << "VoidExpression" << std::endl;
  return (o);
}

#endif	// !VOIDEXPRESSION_HPP_
