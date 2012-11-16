
#ifndef WHILE_HPP_
# define WHILE_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant/recursive_wrapper.hpp>

# include <vector>

# include "SimpleExpression.hpp"

# include "Break.hpp"

struct Expression;

struct While
{
  SimpleExpression condition;
  typedef std::vector<boost::variant<
    boost::recursive_wrapper<Expression>, Break>
    > Type;
  Type then;
};

BOOST_FUSION_ADAPT_STRUCT(While,
			  (SimpleExpression, condition)
			  (While::Type, then)
			  )

//std::ostream &operator<<(std::ostream& o, const While&);

#endif	// !WHILE_HPP_
