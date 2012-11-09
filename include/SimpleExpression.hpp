#ifndef SIMPLEEXPRESSION_HPP_
# define SIMPLEEXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>
# include <boost/tuple/tuple.hpp>

# include "Variable.hpp"

struct List;

# include "List.hpp"

struct CACA;

struct SimpleExpression
{
  typedef boost::variant<int
			 // , boost::tuple<List, SimpleExpression>
			 , boost::recursive_wrapper<CACA>
			 , Variable> TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(SimpleExpression,
			  (SimpleExpression::TypeValue, value)
			  )

struct CACA
{
  List t1;
  SimpleExpression t2;
};

BOOST_FUSION_ADAPT_STRUCT(CACA,
			  (List, t1)
			  (SimpleExpression, t2)
			  )


// typedef boost::variant<int, Variable> SimpleExpression;

std::ostream &operator<<(std::ostream &o, const SimpleExpression &s);

std::ostream &operator<<(std::ostream &o, const boost::tuple<List, SimpleExpression> &t);

std::ostream &operator<<(std::ostream &o, const CACA &c);

#endif	// !SIMPLEEXPRESSION_HPP_
