
#ifndef VOIDEXPRESSION_HPP_
# define VOIDEXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "If.hpp"
# include "While.hpp"

struct VoidExpression
{
  typedef boost::variant<// If, 
			 While
			 > TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(VoidExpression,
			  (VoidExpression::TypeValue, value)
			  )

std::ostream &operator<<(std::ostream& o, const VoidExpression&);

#endif	// !VOIDEXPRESSION_HPP_
