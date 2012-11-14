
#include <iostream>

#include "Somme.hpp"

std::ostream &operator<<(std::ostream &o, const Somme &v)
{
  o << "Somme" << std::endl;
  return (o);
}
