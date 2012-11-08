#ifndef LIST_HPP_
# define LIST_HPP_

# include <boost/fusion/include/adapt_struct.hpp>

# include <boost/variant.hpp>

# include <iosfwd>

# include <boost/variant/recursive_variant.hpp>

# include "Variable.hpp"
# include "SimpleExpression.hpp"

struct List
{
  typedef unsigned int TypeName;
  TypeName name;
};

BOOST_FUSION_ADAPT_STRUCT(List,
			  (List::TypeName, name)
			  )

std::ostream &operator<<(std::ostream &o, const List &l);

// struct ListRvalue;

// struct IntFunction
// {
//   SimpleExpression s;
// };

// BOOST_FUSION_ADAPT_STRUCT(IntFunction,
// 			  (SimpleExpression, s)
// 			  )

// typedef boost::variant<IntFunction> ListFunction;

struct ListConst
{
  typedef std::vector<SimpleExpression> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(ListConst,
			  (ListConst::Type, value)
			  )

struct ListRvalue
{
  typedef boost::variant<
    List,
    // boost::recursive_wrapper<
    ListConst // >
    // , ListFunction
    > Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(ListRvalue,
			  (ListRvalue::Type, value)
			  )

std::ostream &operator<<(std::ostream &o, const ListRvalue &l);

std::ostream &operator<<(std::ostream &o, const ListConst &l);

#endif	// !LIST_HPP_
