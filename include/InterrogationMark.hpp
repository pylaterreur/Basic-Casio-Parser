#ifndef INTERROGATIONMARK_HPP_
# define INTERROGATIONMARK_HPP_

# include <boost/fusion/include/adapt_struct.hpp>

# include "NumericLvalue.hpp"

struct InterrogationMark
{
  NumericLvalue d;
};

BOOST_FUSION_ADAPT_STRUCT(InterrogationMark,
			  (NumericLvalue, d)
			  )

#endif	// !INTERROGATIONMARK_HPP_
