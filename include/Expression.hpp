#ifndef EXPRESSION_HPP_
# define EXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>
# include <boost/tuple/tuple.hpp>

# include "Somme.hpp"
# include "VoidExpression.hpp"

struct Expression
{
  typedef boost::variant<// Assignment,
			 Somme,
			 VoidExpression
			 > TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(Expression,
			  (Expression::TypeValue, value)
			  )

std::ostream &operator<<(std::ostream &o, const Expression &);

#endif	// !EXPRESSION_HPP_
