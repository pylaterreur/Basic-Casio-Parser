#ifndef MATRIX_HPP_
# define MATRIX_HPP_

# include <vector>

# include <boost/fusion/include/adapt_struct.hpp>

# include "SimpleExpression.hpp"

struct SimpleExpression;

struct Matrix
{
  typedef char TypeName;
  TypeName name;
};

BOOST_FUSION_ADAPT_STRUCT(Matrix,
			  (Matrix::TypeName, name)
			  )

struct MatrixConst
{
  typedef std::vector<std::vector<SimpleExpression> > Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(MatrixConst,
			  (MatrixConst::Type, value)
			  )

struct MatrixRvalue
{
  typedef boost::variant<
    Matrix,
    // boost::recursive_wrapper<
    MatrixConst // >
    // , ListFunction
    > Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(MatrixRvalue,
			  (MatrixRvalue::Type, value)
			  )

#endif	// !MATRIX_HPP_
