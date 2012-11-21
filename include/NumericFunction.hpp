#ifndef NUMERIC_FUNCTION_
# define NUMERIC_FUNCTION_

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "functions/Abs.hpp"
# include "functions/Int.hpp"
# include "functions/GetKey.hpp"
# include "functions/Gcd.hpp"
# include "functions/Frac.hpp"

struct NumericFunction
{
  typedef boost::variant<Abs, Int, GetKey, Gcd, Frac> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(NumericFunction,
			  (NumericFunction::Type, value)
			  )

#endif	// !NUMERIC_FUNCTION_
