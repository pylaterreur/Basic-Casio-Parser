#ifndef SIMPLEEXPRESSION_HPP_
# define SIMPLEEXPRESSION_HPP_

# include <iosfwd>

# include <boost/variant/recursive_wrapper.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>
# include <boost/tuple/tuple.hpp>

# include "NumericFunction.hpp"
# include "Variable.hpp"

struct List;
struct Somme;

# include "List.hpp"

struct ListIndex;

struct SimpleExpression
{
  typedef boost::variant<int
			 , NumericFunction
			 // , boost::tuple<List, SimpleExpression>
			 , boost::recursive_wrapper<ListIndex>
			 , Variable
			 , boost::recursive_wrapper<Somme>
			 > TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(SimpleExpression,
			  (SimpleExpression::TypeValue, value)
			  )

struct ListIndex
{
  List t1;
  SimpleExpression t2;
};

BOOST_FUSION_ADAPT_STRUCT(ListIndex,
			  (List, t1)
			  (SimpleExpression, t2)
			  )


// typedef boost::variant<int, Variable> SimpleExpression;

std::ostream &operator<<(std::ostream &o, const SimpleExpression &s);

std::ostream &operator<<(std::ostream &o, const boost::tuple<List, SimpleExpression> &t);

std::ostream &operator<<(std::ostream &o, const ListIndex &c);

#endif	// !SIMPLEEXPRESSION_HPP_
