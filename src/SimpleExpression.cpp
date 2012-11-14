
#include <iostream>

#include "SimpleExpression.hpp"

std::ostream &operator<<(std::ostream &o, const SimpleExpression &s)
{
  o << "SimpleExpression" // << s.value
    ;
  return (o);
}

std::ostream &operator<<(std::ostream &o, const boost::tuple<List, SimpleExpression> &t)
{
  o << "Tuple List " << t.get<0>() << " " << t.get<1>();
  return (o);
}

std::ostream &operator<<(std::ostream &o, const ListIndex &c)
{
  o << c.t1 << " " << c.t2 << std::endl;
  return (o);
}
