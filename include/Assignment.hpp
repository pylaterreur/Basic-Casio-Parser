#ifndef ASSIGNEMENT_HPP_
# define ASSIGNEMENT_HPP_

# include <boost/variant.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"
# include "NumericLvalue.hpp"

struct NumericAssignment
{
  SimpleExpression s;
  NumericLvalue d;
};

BOOST_FUSION_ADAPT_STRUCT(NumericAssignment,
			  (SimpleExpression, s)
			  (NumericLvalue, d)
			  )

struct ListAssignment
{
  ListRvalue s;
  List d;
};

BOOST_FUSION_ADAPT_STRUCT(ListAssignment,
			  (ListRvalue, s)
			  (List, d)
			  )

struct Assignment
{
  typedef boost::variant<NumericAssignment, ListAssignment
			 > Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(Assignment,
			  (Assignment::Type, value)
			  )

#endif	// !ASSIGNEMENT_HPP_
