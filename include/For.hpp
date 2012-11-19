
#ifndef FOR_HPP_
# define FOR_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant/recursive_wrapper.hpp>

# include <vector>

# include "SimpleExpression.hpp"
# include "Assignment.hpp"

# include "Break.hpp"

struct Expression;

struct For
{
  NumericAssignment f;
  SimpleExpression t;
  SimpleExpression s;
  typedef std::vector<boost::variant<
    boost::recursive_wrapper<Expression>, Break>
    > Type;
  Type then;
};

BOOST_FUSION_ADAPT_STRUCT(For,
			  (NumericAssignment, f)
			  (SimpleExpression, t)
			  (SimpleExpression, s)
			  (For::Type, then)
			  )

//std::ostream &operator<<(std::ostream& o, const For&);

#endif	// !FOR_HPP_
