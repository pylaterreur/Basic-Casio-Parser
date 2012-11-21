#ifndef FRAC_HPP_
# define FRAC_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Frac
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Frac,
			  (Frac::Type, parameter)
			  )

#endif	// FRAC_HPP_
