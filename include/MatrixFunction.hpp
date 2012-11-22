#ifndef MATRIX_FUNCTION_
# define MATRIX_FUNCTION_

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "functions/Augment.hpp"

struct MatrixFunction
{
  typedef boost::variant<Augment> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(MatrixFunction,
			  (MatrixFunction::Type, value)
			  )

#endif	// !MATRIX_FUNCTION_
