
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

    abs_ = lit("Abs ") >> numeric_rvalue_;

    and_ = lit(" And ");

    locate_ = lit("Locate ")
      >> numeric_rvalue_ >> ','
      >> numeric_rvalue_ >> ",\""
      >> *(~char_('"')) >> '"';

    comment_ = '\'' >> *(char_ - new_line_);

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

    condition_do_lpwhile_ = lit("Do") >> new_line_
		>> *(!(lit("LpWhile")) >> expression_ >> +new_line_)
		>> lit("LpWhile ") >> numeric_rvalue_;

    or_ = lit(" Or ");

    list_index_ = int_;
    
    list_lvalue_ = lit("List") >> -lit(' ') >> list_index_;

    list_rvalue_ = list_ | ('{' >> (numeric_rvalue_ % ',') >> '}');

    variable_  = char_("A-Z");

    numeric_lvalue_ = (list_rvalue_ >> '[' >> numeric_rvalue_ >> ']') | variable_;

    operator_binary_ = operator_gt_
      | operator_lt_
      | operator_eq_
      | operator_neq_
      | and_
      | or_
      | char_("-+*/")
      ;
    operator_unary_ = char_("-+");

    // doesnt work yet xD
    numeric_rvalue_ = *(char_('(') | operator_unary_) >> (int_ | abs_) >> *char_(')') >> -(operator_binary_ >> numeric_lvalue_);

    void_expression_ =
      locate_
      | condition_if_
      | condition_while_
      | condition_do_lpwhile_
      // | 
      ;

    operator_gt_ = lit('>');
    operator_lt_ = lit('<');
    operator_eq_ = lit('=');
    operator_neq_ = lit("!=");

    expression_ = void_expression_ | list_rvalue_ | matrix_rvalue_ | numeric_rvalue_;

    start_ %= *(expression_ >> +new_line_);
  }

private:

  boost::spirit::qi::rule<Iterator
       // , Program()
       // , boost::variant<int, std::string>()
       > start_;

  boost::spirit::qi::rule<Iterator> new_line_;

  boost::spirit::qi::rule<Iterator> comment_;

  boost::spirit::qi::rule<Iterator> operator_unary_;
  boost::spirit::qi::rule<Iterator> operator_binary_;

  boost::spirit::qi::rule<Iterator> locate_;
  boost::spirit::qi::rule<Iterator> condition_if_;
  boost::spirit::qi::rule<Iterator> condition_while_;
  boost::spirit::qi::rule<Iterator> condition_do_lpwhile_;

  boost::spirit::qi::rule<Iterator> interrogation_mark_;
  boost::spirit::qi::rule<Iterator> abs_;
  boost::spirit::qi::rule<Iterator> and_;
  boost::spirit::qi::rule<Iterator> ans_;
  boost::spirit::qi::rule<Iterator> augment_;

  boost::spirit::qi::rule<Iterator> axesoff_;
  boost::spirit::qi::rule<Iterator> axeson_;
  boost::spirit::qi::rule<Iterator> bg_none_;
  boost::spirit::qi::rule<Iterator> bg_pict_;
  boost::spirit::qi::rule<Iterator> break_;
  boost::spirit::qi::rule<Iterator> circle_;
  boost::spirit::qi::rule<Iterator> clrgraph_;
  boost::spirit::qi::rule<Iterator> clrlist_;
  boost::spirit::qi::rule<Iterator> clrmat_;
  boost::spirit::qi::rule<Iterator> clrtext_;
  boost::spirit::qi::rule<Iterator> cls_;
  boost::spirit::qi::rule<Iterator> coordoff_;
  boost::spirit::qi::rule<Iterator> coordon_;
  boost::spirit::qi::rule<Iterator> cross_;

  boost::spirit::qi::rule<Iterator> or_;


  boost::spirit::qi::rule<Iterator> operator_gt_;
  boost::spirit::qi::rule<Iterator> operator_lt_;
  boost::spirit::qi::rule<Iterator> operator_eq_;
  boost::spirit::qi::rule<Iterator> operator_neq_;



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
};

#endif	// !PARSER_HPP_
