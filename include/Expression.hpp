#ifndef EXPRESSION_HPP_
# define EXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>
# include <boost/variant/recursive_wrapper.hpp>

# include "Boolean.hpp"
# include "VoidExpression.hpp"
# include "InterrogationMark.hpp"

# include "Matrix.hpp"

struct VoidExpression;

struct Expression
{
  typedef boost::variant<
    Boolean,
    boost::recursive_wrapper<VoidExpression>,
    InterrogationMark
    , MatrixRvalue
    > TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(Expression,
			  (Expression::TypeValue, value)
			  )

std::ostream &operator<<(std::ostream &o, const Expression &);

#endif	// !EXPRESSION_HPP_
