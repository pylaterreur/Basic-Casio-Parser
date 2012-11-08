
#include <iostream>

#include "List.hpp"

std::ostream &operator<<(std::ostream &o, const List &l)
{
  o << "List: " << l.name;
  return (o);
}

std::ostream &operator<<(std::ostream &o, const ListRvalue &l)
{
  o << "ListRvalue: " << l.value;
  return (o);
}

std::ostream &operator<<(std::ostream &o, const ListConst &l)
{
  o << "List : {" << std::endl;
  std::for_each(l.value.begin(), l.value.end(), [&o](const SimpleExpression &s){ o << s << std::endl; });
  o << "}" << std::endl;
  return (o);
}
