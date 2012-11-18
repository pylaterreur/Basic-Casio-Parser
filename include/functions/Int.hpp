#ifndef INT_HPP_
# define INT_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Int
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Int,
			  (Int::Type, parameter)
			  )

#endif	// INT_HPP_
