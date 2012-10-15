
#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/spirit/include/qi.hpp>

# include "Program.hpp"

using namespace boost::spirit::qi;

template <typename Iterator>
class Parser : public grammar<Iterator
			      // , Program()
			      , int()
			      >
{
public:
  Parser() : Parser::base_type(start_, "start")
  {
    // rule<Iterator> newline = char_('\n') | char_(':');
    // start_ %= (char_('\'') >> +(char_ - newline) >> newline);

    start_ %= int_;
  }

private:
  rule<Iterator
       // , Program()
       , int()
       > start_;
};

#endif	// !PARSER_HPP_
