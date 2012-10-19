
#ifndef NUMERICEXPRESSION_HPP_
# define NUMERICEXPRESSION_HPP_

# include <string>
# include <boost/spirit/include/qi.hpp>
# include <boost/tuple/tuple.hpp>
# include "Parser.hpp"

template <typename Iterator>
class NumericExpression;

template <typename Iterator>
struct AttributeType<NumericExpression<Iterator> >
{
  typedef int attribute_type;
};

template <typename Iterator>
class NumericExpression : public AttributeType<NumericExpression<Iterator> >,
			  public boost::spirit::qi::grammar<Iterator,
							    typename AttributeType<NumericExpression<Iterator> >::attribute_type()>
{
public:
  struct Toto
  {
    typedef boost::tuple<int, int, std::string> attribute_type;
  };
  using typename AttributeType<NumericExpression<Iterator> >::attribute_type;

  NumericExpression() : NumericExpression::base_type(start_, "numeric_expression")
  {
    start_ %= boost::spirit::qi::int_;
  }

private:
  boost::spirit::qi::rule<Iterator, attribute_type()> start_;
};

#endif	// !NUMERICEXPRESSION_HPP_
