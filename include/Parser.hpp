
#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/spirit/include/qi.hpp>
# include <boost/variant.hpp>

# include "Program.hpp"

template <typename Iterator>
class Parser : public boost::spirit::qi::grammar<Iterator
						 // , Program()
						 // , boost::variant<int, std::string>()
						 >
{
public:
  Parser() : Parser::base_type(start_, "start")
  {
    using namespace boost::spirit::qi;

    new_line_ = lit('\n') | ':';

    locate_ = lit("Locate ")
      >> numeric_rvalue_ >> ','
      >> numeric_rvalue_ >> ",\""
      >> *(~char_('"')) >> '"';

    condition_if_ = lit("If ")
      >> numeric_rvalue_ >> new_line_
      >> lit("Then ")
      >> *(!(lit("IfEnd") | lit("Else")) >> expression_ >> +new_line_)
      >> -(
	   lit("Else ")
	   >> *(!lit("IfEnd") >> expression_ >> +new_line_)
	   )
      >> lit("IfEnd");

    condition_while_ = lit("While ")
      >> numeric_rvalue_ >> new_line_
      >> *(!(lit("WhileEnd")) >> expression_ >> +new_line_)
      >> lit("WhileEnd");


    list_index_ = int_;
    
    list_lvalue_ = lit("List") >> -lit(' ') >> list_index_;

    list_rvalue_ = list_ | ('{' >> (numeric_rvalue_ % ',') >> '}');

    variable_  = char_("A-Z");

    numeric_lvalue_ = (list_rvalue_ >> '[' >> numeric_rvalue_ >> ']') | variable_;

    numeric_rvalue_ = int_ | numeric_lvalue_;

    void_expression_ = locate_ | condition_if_;

    expression_ = void_expression_ | list_rvalue_ | matrix_rvalue_ | numeric_rvalue_
      ;

    start_ %= *(expression_ >> +new_line_);
  }

private:

  boost::spirit::qi::rule<Iterator
       // , Program()
       // , boost::variant<int, std::string>()
       > start_;

  boost::spirit::qi::rule<Iterator> new_line_;

  boost::spirit::qi::rule<Iterator> temp;

  boost::spirit::qi::rule<Iterator> void_expression_;
  boost::spirit::qi::rule<Iterator> numeric_lvalue_;
  boost::spirit::qi::rule<Iterator> numeric_rvalue_;
  boost::spirit::qi::rule<Iterator> list_lvalue_;
  boost::spirit::qi::rule<Iterator> list_rvalue_;
  boost::spirit::qi::rule<Iterator> matrix_lvalue_;
  boost::spirit::qi::rule<Iterator> matrix_rvalue_;
  boost::spirit::qi::rule<Iterator> expression_;

  boost::spirit::qi::rule<Iterator> list_index_;

  boost::spirit::qi::rule<Iterator> variable_;
  boost::spirit::qi::rule<Iterator> list_;
  boost::spirit::qi::rule<Iterator> matrix_;

  boost::spirit::qi::rule<Iterator> locate_;
  boost::spirit::qi::rule<Iterator> condition_if_;
  boost::spirit::qi::rule<Iterator> condition_while_;
};

#endif	// !PARSER_HPP_
