
#ifndef DOUBLEARROW_HPP_
# define DOUBLEARROW_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant/recursive_wrapper.hpp>

# include "SimpleExpression.hpp"
# include "Expression.hpp"

struct Expression;

struct DoubleArrow
{
  SimpleExpression condition;
  typedef boost::recursive_wrapper<Expression> Type;
  Type then;
};

BOOST_FUSION_ADAPT_STRUCT(DoubleArrow,
			  (SimpleExpression, condition)
			  (DoubleArrow::Type, then)
			  )

//std::ostream &operator<<(std::ostream& o, const DoubleArrow&);

#endif	// !DOUBLEARROW_HPP_
