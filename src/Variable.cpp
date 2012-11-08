
#include <iostream>

#include "Variable.hpp"

std::ostream &operator<<(std::ostream &o, const Variable &v)
{
  o << "Variable: " << v.name;
  return (o);
}
