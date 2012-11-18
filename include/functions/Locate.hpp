#ifndef LOCATE_HPP_
# define LOCATE_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Locate
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter1;
  Type parameter2;
  std::string parameter3;
};

BOOST_FUSION_ADAPT_STRUCT(Locate,
			  (Locate::Type, parameter1)
			  (Locate::Type, parameter2)
			  (std::string, parameter3)
			  )

#endif	// LOCATE_HPP_
