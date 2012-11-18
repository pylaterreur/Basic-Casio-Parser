#ifndef NUMERIC_FUNCTION_
# define NUMERIC_FUNCTION_

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "functions/Abs.hpp"
# include "functions/Int.hpp"

struct NumericFunction
{
  typedef boost::variant<Abs, Int> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(NumericFunction,
			  (NumericFunction::Type, value)
			  )

#endif	// !NUMERIC_FUNCTION_
