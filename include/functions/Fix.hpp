#ifndef FIX_HPP_
# define FIX_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct Fix
{
  typedef SimpleExpression Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Fix,
			  (Fix::Type, parameter)
			  )

#endif	// FIX_HPP_
