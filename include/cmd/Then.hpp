
#ifndef THEN_HPP_
# define THEN_HPP_

# include <string>
# include <boost/spirit/include/qi.hpp>
# include <boost/tuple/tuple.hpp>
# include "Parser.hpp"
# include "NumericExpression.hpp"

template <typename Iterator>
class Then;

template <typename Iterator>
struct AttributeType<Then<Iterator> >
{
  typedef int attribute_type;
};

template <typename Iterator>
class Then : public AttributeType<Then<Iterator> >,
	   public boost::spirit::qi::grammar<Iterator,
					     typename AttributeType<Then<Iterator> >::attribute_type()>
{
public:
  using typename AttributeType<Then<Iterator> >::attribute_type;

  Then() : Then::base_type(start_, "then")
  {
    start_ %= boost::spirit::qi::lit("Then ")
      >> numeric_expression_ >> then_;
  }

private:
  boost::spirit::qi::rule<Iterator> start_;
};

#endif	// !THEN_HPP_
