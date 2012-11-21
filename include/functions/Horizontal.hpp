#ifndef HORIZONTAL_HPP_
# define HORIZONTAL_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Horizontal
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Horizontal,
			  (Horizontal::Type, parameter)
			  )

#endif	// HORIZONTAL_HPP_
