#ifndef ISZ_HPP_
# define ISZ_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "NumericLvalue.hpp"

struct Isz
{
  typedef boost::recursive_wrapper<NumericLvalue> Type;
  Type parameter;
};

BOOST_FUSION_ADAPT_STRUCT(Isz,
			  (Isz::Type, parameter)
			  )

#endif	// ISZ_HPP_
