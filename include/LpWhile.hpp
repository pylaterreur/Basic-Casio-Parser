
#ifndef LPWHILE_HPP_
# define LPWHILE_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant/recursive_wrapper.hpp>

# include <vector>

# include "SimpleExpression.hpp"

struct Expression;

struct LpWhile
{
  typedef std::vector<
    boost::recursive_wrapper<Expression>
    > Type;
  Type then;
  SimpleExpression condition;
};

BOOST_FUSION_ADAPT_STRUCT(LpWhile,
			  (LpWhile::Type, then)
			  (SimpleExpression, condition)
			  )

//std::ostream &operator<<(std::ostream& o, const LpLpWhile&);

#endif	// !LPWHILE_HPP_
