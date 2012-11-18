#ifndef ABS_HPP_
# define ABS_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Abs
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Abs,
			  (Abs::Type, parameter)
			  )

#endif	// ABS_HPP_
