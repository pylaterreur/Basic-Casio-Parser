
#ifndef IF_HPP_
# define IF_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant/recursive_wrapper.hpp>
# include <boost/optional.hpp>

# include <vector>

# include "SimpleExpression.hpp"
# include "Expression.hpp"

struct Expression;

struct If
{
  SimpleExpression condition;
  typedef std::vector<boost::recursive_wrapper<Expression> > Type;
  //  typedef boost::recursive_wrapper<Expression> Type;
  Type then;
  typedef Type ElseType;
  ElseType elsethen;
};

BOOST_FUSION_ADAPT_STRUCT(If,
			  (SimpleExpression, condition)
			  (If::Type, then)
			  (If::ElseType, elsethen)
			  )

//std::ostream &operator<<(std::ostream& o, const If&);

#endif	// !IF_HPP_
