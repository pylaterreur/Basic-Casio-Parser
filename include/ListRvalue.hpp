
#ifndef LISTRVALUE_HPP_
# define LISTRVALUE_HPP_

#include <iosfwd>

struct ListRvalue
{};

std::ostream &operator<<(std::ostream& o, const ListRvalue&)
{
  o << "ListRvalue" << std::endl;
  return (o);
}

#endif	// !LISTRVALUE_HPP_
