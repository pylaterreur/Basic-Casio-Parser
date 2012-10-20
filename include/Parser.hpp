
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

    and_ = lit(" And ");


    interrogation_mark_ = '?';
    ans_ = lit("Ans");
    augment_ = "Augment(" >> matrix_rvalue_ >> ',' >> matrix_rvalue_ >> ')';

    axesoff_ = lit("AxesOff");
    axeson_ = lit("AxesOn");
    bg_none_ = lit("BG-None");
    bg_pict_ = lit("BG-Pict ") >> int_;
    break_ = lit("Break");
    circle_ = lit("Circle ") >> numeric_rvalue_ >> ',' >> numeric_rvalue_ >> ',' >> numeric_rvalue_;
    clrgraph_ = lit("ClrGraph");
    clrlist_ = lit("ClrList ") >> -(list_index_);
    clrmat_ = lit("ClrMat") >> -(mat_index_);
    clrtext_ = lit("ClrText");
    cls_ = lit("Cls");
    coordoff_ = lit("CoordOff");
    coordon_ = lit("CoordOn");
    cross_ = lit("Cross");
    deg_ = "Deg";
    derivoff_ = "DerivOff";
    derivon_ = "DerivOn";
    dim_matrix_ = "Dim " >> matrix_lvalue_;
    dim_list_ = "Dim " >> list_lvalue_;
    dot_ = "Dot";
    drawdyna_ = "DrawDyna";
    drawgraph_ = "DrawGraph";
    drawoff_ = "DrawOff";
    drawon_ = "DrawOn";
    drawstat_ = "DrawStat";
    dsz_ = "Dsz " >> numeric_lvalue_;
    fline_ = "F-Line "
      >> numeric_rvalue_ >> ','
      >> numeric_rvalue_ >> ','
      >> numeric_rvalue_ >> ','
      >> numeric_rvalue_;
    file_index_ = int_;
    file_ = "File" >> file_index_;
    fix_ = "Fix " >> numeric_rvalue_;
    frac_ = "Frac " >> numeric_rvalue_;
    gconnect_ = "G-Connect";
    gplot_ = "G-Plot";
    gcd_ = "GCD(" >> numeric_rvalue_ >> ',' >> numeric_rvalue_ >> ')';
    getkey_ = "Getkey";
    goto_ = "Goto " >> label_index_;
    gra_ = "Gra";
    gridoff_ = "GridOff";
    gridon_ = "GridOn";
    horizontal_ = "Horizontal " >> numeric_rvalue_;
    isz_ = "Isz " >> numeric_lvalue_;
    labeloff_ = "LabelOff";
    labelon_ = "LabelOn";


    label_index_ = char_("0-9A-Z");

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
      >> *(!(lit("WhileEnd")) >> loop_expression_ >> +new_line_)
      >> lit("WhileEnd");

    condition_do_lpwhile_ = lit("Do") >> new_line_
		>> *(!(lit("LpWhile ")) >> loop_expression_ >> +new_line_)
		>> lit("LpWhile ") >> numeric_rvalue_;

    condition_for_ = lit("For ") >> numeric_rvalue_ >> simple_arrow_ >> numeric_lvalue_ >> " To "
				 >> numeric_rvalue_ >> " Step " >> numeric_rvalue_ >>  new_line_
		>> *(!(lit("Next")) >> loop_expression_ >> +new_line_)
		>> lit("Next");

    loop_expression_ = break_ | expression_;

    or_ = lit(" Or ");

    list_index_ = int_;
    mat_index_ = char_("A-Z") | ans_;
    
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

    number_ = int_;

    simple_arrow_ = lit("->");
    double_arrow_ = lit("=>");

    assignment_ = (numeric_rvalue_ >> simple_arrow_ >> (numeric_lvalue_ | dim_list_))
      | (list_rvalue_ >> simple_arrow_ >> (list_lvalue_ | dim_matrix_))
      | (matrix_rvalue_ >> simple_arrow_ >> matrix_lvalue_)
      ;

    void_expression_ =
      locate_
      | augment_
      | axesoff_
      | axeson_
      | bg_none_
      | bg_pict_
      | break_
      | circle_
      | clrgraph_
      | clrlist_
      | clrmat_
      | clrtext_
      | cls_
      | coordoff_
      | coordon_
      | deg_
      | derivoff_
      | derivon_
      | drawdyna_
      | drawgraph_
      | drawstat_
      | dsz_
      | fline_
      | file_
      | fix_
      | gconnect_
      | gplot_
      | goto_
      | gra_
      | gridoff_
      | gridon_
      | horizontal_
      | isz_
      | labeloff_
      | labelon_
      | condition_if_
      | condition_while_
      | condition_do_lpwhile_
      | condition_for_
      | assignment_
      // | 
      ;

    operator_gt_ = lit('>');
    operator_lt_ = lit('<');
    operator_eq_ = lit('=');
    operator_neq_ = lit("!=");

    expression_no_comment_ = void_expression_ | list_rvalue_ | matrix_rvalue_ | numeric_rvalue_;
    expression_ = comment_ | expression_no_comment_;

    // doesnt work yet xD
    numeric_rvalue_ = eps >> arithmetic.expression;

    start_ %= *(expression_ >> +new_line_);
  }

private:

  boost::spirit::qi::rule<Iterator
       // , Program()
       // , boost::variant<int, std::string>()
       > start_;

  struct Arithmetic
  {
    typedef boost::spirit::qi::rule<Iterator> r;

    r expression;
    r number;
    r constant;
    r add;
    r multiply;
    r variable;
    r digit;
    r unary;
    r term;
    r function;
    r simple_expression;


    r abs_;
    r int_f_;
    r intg_;

    Arithmetic()
    {
      using namespace boost::spirit::qi;

      abs_ = lit("Abs ") >> simple_expression;
      int_f_ = lit("Int ") >> simple_expression;
      intg_ = lit("Intg ") >> simple_expression;
     
      function = int_f_ | intg_ | abs_;
      unary = char_('-') | char_('+');
      variable = char_("A-Z");
      digit = char_("0-9");
      number = +digit;
      constant = *unary >> (function | number | variable);
      simple_expression = (char_('(') >> expression >> char_(')'))
	| constant;
      add = char_("+");
      multiply = char_("*");
      term = constant >> *(multiply >> constant);
      expression = (term >> *(add >> term)) | simple_expression;
    }
  } arithmetic;


  boost::spirit::qi::rule<Iterator> new_line_;

  boost::spirit::qi::rule<Iterator> label_index_;

  boost::spirit::qi::rule<Iterator> assignment_;
  boost::spirit::qi::rule<Iterator> number_;

  boost::spirit::qi::rule<Iterator> double_arrow_;
  boost::spirit::qi::rule<Iterator> simple_arrow_;

  boost::spirit::qi::rule<Iterator> comment_;

  boost::spirit::qi::rule<Iterator> operator_unary_;
  boost::spirit::qi::rule<Iterator> operator_binary_;

  boost::spirit::qi::rule<Iterator> locate_;
  boost::spirit::qi::rule<Iterator> condition_if_;
  boost::spirit::qi::rule<Iterator> condition_while_;
  boost::spirit::qi::rule<Iterator> condition_do_lpwhile_;
  boost::spirit::qi::rule<Iterator> condition_for_;

  boost::spirit::qi::rule<Iterator> interrogation_mark_;
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
  boost::spirit::qi::rule<Iterator> deg_;
  boost::spirit::qi::rule<Iterator> derivon_;
  boost::spirit::qi::rule<Iterator> derivoff_;
  boost::spirit::qi::rule<Iterator> dim_matrix_;
  boost::spirit::qi::rule<Iterator> dim_list_;
  boost::spirit::qi::rule<Iterator> dot_;
  boost::spirit::qi::rule<Iterator> drawdyna_;
  boost::spirit::qi::rule<Iterator> drawgraph_;
  boost::spirit::qi::rule<Iterator> drawoff_;
  boost::spirit::qi::rule<Iterator> drawon_;
  boost::spirit::qi::rule<Iterator> drawstat_;
  boost::spirit::qi::rule<Iterator> dsz_;
  boost::spirit::qi::rule<Iterator> fline_;
  boost::spirit::qi::rule<Iterator> file_;
  boost::spirit::qi::rule<Iterator> fix_;
  boost::spirit::qi::rule<Iterator> frac_;
  boost::spirit::qi::rule<Iterator> gconnect_;
  boost::spirit::qi::rule<Iterator> gplot_;
  boost::spirit::qi::rule<Iterator> gcd_;
  boost::spirit::qi::rule<Iterator> getkey_;
  boost::spirit::qi::rule<Iterator> goto_;
  boost::spirit::qi::rule<Iterator> gra_;
  boost::spirit::qi::rule<Iterator> gridoff_;
  boost::spirit::qi::rule<Iterator> gridon_;
  boost::spirit::qi::rule<Iterator> horizontal_;
  boost::spirit::qi::rule<Iterator> isz_;
  boost::spirit::qi::rule<Iterator> labeloff_;
  boost::spirit::qi::rule<Iterator> labelon_;

  // not done yet
  boost::spirit::qi::rule<Iterator> lbl_;
  boost::spirit::qi::rule<Iterator> lcm_;
  boost::spirit::qi::rule<Iterator> line_;
  boost::spirit::qi::rule<Iterator> list_mat_;
  boost::spirit::qi::rule<Iterator> max_;

  // end not done yet

  boost::spirit::qi::rule<Iterator> or_;

  boost::spirit::qi::rule<Iterator> file_index_;

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
  boost::spirit::qi::rule<Iterator> expression_no_comment_;
  boost::spirit::qi::rule<Iterator> loop_expression_;

  boost::spirit::qi::rule<Iterator> list_index_;
  boost::spirit::qi::rule<Iterator> mat_index_;

  boost::spirit::qi::rule<Iterator> variable_;
  boost::spirit::qi::rule<Iterator> list_;
  boost::spirit::qi::rule<Iterator> matrix_;
};

#endif	// !PARSER_HPP_
