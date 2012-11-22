#ifndef AUGMENT_HPP_
# define AUGMENT_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "Matrix.hpp"

struct MatrixRvalue;

struct Augment
{
  typedef boost::recursive_wrapper<MatrixRvalue> Type;
  Type parameter1;
  Type parameter2;
};

BOOST_FUSION_ADAPT_STRUCT(Augment,
			  (Augment::Type, parameter1)
			  (Augment::Type, parameter2)
			  )

#endif	// AUGMENT_HPP_
