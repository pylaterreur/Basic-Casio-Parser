
#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/spirit/include/qi.hpp>
# include <boost/variant.hpp>

template <typename T>
struct AttributeType;

# include "Program.hpp"
# include "cmd/Locate.hpp"

using namespace boost::spirit::qi;

template <typename Iterator>
class Parser : public grammar<Iterator
			      // , Program()
			      // , boost::variant<int, std::string>()
			      >
{
public:
  Parser() : Parser::base_type(start_, "start")
  {
    // rule<Iterator> newline = char_('\n') | char_(':');
    // start_ %= (char_('\'') >> +(char_ - newline) >> newline);

    finish_ = locate_ % '\n';
       //finish_ = lit("Locate ") >> int_ >> ',' >> int_;
    start_ %= (int_ | string("LOL")) >> *finish_;
  }

private:
  rule<Iterator
       // , Program()
       // , boost::variant<int, std::string>()
       > start_;

  Locate<Iterator> locate_;
  rule<Iterator, boost::tuple<int, int, std::string> > finish_;
};

#endif	// !PARSER_HPP_
