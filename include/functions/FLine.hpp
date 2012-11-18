#ifndef FLINE_HPP_
# define FLINE_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct FLine
{
  typedef boost::recursive_wrapper<SimpleExpression> Type;
  Type parameter1;
  Type parameter2;
  Type parameter3;
  Type parameter4;
};

BOOST_FUSION_ADAPT_STRUCT(FLine,
			  (FLine::Type, parameter1)
			  (FLine::Type, parameter2)
			  (FLine::Type, parameter3)
			  )

#endif	// FLINE_HPP_
