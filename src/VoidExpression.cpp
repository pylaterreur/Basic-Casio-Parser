
#include <iostream>

#include "VoidExpression.hpp"

std::ostream &operator<<(std::ostream& o, const VoidExpression&)
{
  o << "VoidExpression" << std::endl;
  return (o);
}
