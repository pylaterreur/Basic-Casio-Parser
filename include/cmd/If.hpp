
#ifndef IF_HPP_
# define IF_HPP_

# include <string>
# include <boost/spirit/include/qi.hpp>
# include <boost/tuple/tuple.hpp>
# include "Parser.hpp"
# include "NumericExpression.hpp"

template <typename Iterator>
class If;

template <typename Iterator>
struct AttributeType<If<Iterator> >
{
  typedef int attribute_type;
};

template <typename Iterator>
class If : public AttributeType<If<Iterator> >,
	   public boost::spirit::qi::grammar<Iterator,
					     typename AttributeType<If<Iterator> >::attribute_type()>
{
public:
  using typename AttributeType<If<Iterator> >::attribute_type;

  If() : If::base_type(start_, "if")
  {
    start_ %= boost::spirit::qi::lit("If ")
      >> numeric_expression_ >> '\n'
      >> boost::spirit::qi::lit("Then ") >> (numeric_expression_ % '\n')
      >> '\n'
      >> boost::spirit::qi::lit("IfEnd");
  }

private:
  boost::spirit::qi::rule<Iterator, attribute_type()> start_;
  NumericExpression<Iterator> numeric_expression_;
};

#endif	// !IF_HPP_
