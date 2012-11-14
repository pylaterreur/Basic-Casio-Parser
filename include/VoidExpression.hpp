
#ifndef VOIDEXPRESSION_HPP_
# define VOIDEXPRESSION_HPP_

#include <iosfwd>

struct VoidExpression
{};

std::ostream &operator<<(std::ostream& o, const VoidExpression&);

#endif	// !VOIDEXPRESSION_HPP_
