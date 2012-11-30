#ifndef CLRMAT_HPP_
# define CLRMAT_HPP_

# include <boost/optional.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "Matrix.hpp"

struct ClrMat
{
  typedef boost::optional<Matrix::TypeName> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(ClrMat,
			  (ClrMat::Type, value)
			  )

#endif	// CLRMAT_HPP_
