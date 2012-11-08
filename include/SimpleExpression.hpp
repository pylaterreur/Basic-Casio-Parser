#ifndef SIMPLEEXPRESSION_HPP_
# define SIMPLEEXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>
# include <boost/tuple/tuple.hpp>

# include "Variable.hpp"

struct List;

# include "List.hpp"

struct SimpleExpression
{
  typedef boost::variant<int, Variable> TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(SimpleExpression,
			  (SimpleExpression::TypeValue, value)
			  )

// typedef boost::variant<int, Variable> SimpleExpression;

std::ostream &operator<<(std::ostream &o, const SimpleExpression &s);

std::ostream &operator<<(std::ostream &o, const boost::tuple<List, SimpleExpression> &t);

#endif	// !SIMPLEEXPRESSION_HPP_
