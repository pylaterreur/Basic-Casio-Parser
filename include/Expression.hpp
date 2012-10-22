
#ifndef EXPRESSION_HPP_
# define EXPRESSION_HPP_

# include <boost/variant.hpp>
# include "Comment.hpp"
# include "VoidExpression.hpp"
# include "ListRvalue.hpp"
# include "MatrixRvalue.hpp"
# include "NumericRvalue.hpp"

// typedef boost::variant<Comment, VoidExpression, ListRvalue, MatrixRvalue, NumericRvalue> Expression;

struct Expression
{
  typedef boost::variant<Comment, VoidExpression, ListRvalue, MatrixRvalue, NumericRvalue> type;
  type expression_;
};

BOOST_FUSION_ADAPT_STRUCT(
			  Expression,
			  (Expression::type, expression_)
			  )

#endif	// !EXPRESSION_HPP_
