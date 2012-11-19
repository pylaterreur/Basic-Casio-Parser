#ifndef DSZ_HPP_
# define DSZ_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "NumericLvalue.hpp"

struct Dsz
{
  typedef boost::recursive_wrapper<NumericLvalue> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Dsz,
			  (Dsz::Type, parameter)
			  )

#endif	// DSZ_HPP_
