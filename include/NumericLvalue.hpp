// NEED TO DO THIS FILE
#ifndef NUMERICLVALUE_HPP_
# define NUMERICLVALUE_HPP_

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "Variable.hpp"
# include "SimpleExpression.hpp"
# include "List.hpp"

struct ListIndex;

struct NumericLvalue
{
  typedef
  boost::variant<Variable, ListIndex// , DimList
		 >
  Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(NumericLvalue,
			  (NumericLvalue::Type, value)
			  )

#endif	// !NUMERICLVALUE_HPP_
