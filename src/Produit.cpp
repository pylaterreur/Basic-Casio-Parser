
#include <iostream>

#include "Produit.hpp"

std::ostream &operator<<(std::ostream &o, const Produit &v)
{
  o << "Produit" << std::endl;
  return (o);
}
