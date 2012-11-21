#ifndef GCD_HPP_
# define GCD_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Gcd
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter1;
  Type parameter2;
};

BOOST_FUSION_ADAPT_STRUCT(Gcd,
			  (Gcd::Type, parameter1)
			  (Gcd::Type, parameter2)
			  )

#endif	// GCD_HPP_
