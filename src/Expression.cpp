
#include <iostream>

#include "Expression.hpp"

std::ostream &operator<<(std::ostream &o, const Expression &s)
{
  o << "Expression" << s.value;
  return (o);
}
