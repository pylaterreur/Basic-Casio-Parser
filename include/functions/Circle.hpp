#ifndef CIRCLE_HPP_
# define CIRCLE_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Circle
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter1;
  Type parameter2;
  Type parameter3;
};

BOOST_FUSION_ADAPT_STRUCT(Circle,
			  (Circle::Type, parameter1)
			  (Circle::Type, parameter2)
			  (Circle::Type, parameter3)
			  )

#endif	// CIRCLE_HPP_
