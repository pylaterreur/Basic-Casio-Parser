
#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix.hpp>
# include <boost/variant.hpp>

# include "Expression.hpp"

# include "Comment.hpp"
# include "Variable.hpp"
# include "List.hpp"
# include "SimpleExpression.hpp"
# include "Produit.hpp"
# include "Somme.hpp"

# include "While.hpp"

# include "Break.hpp"

typedef
// SimpleExpression
// List
// ListRvalue
// Produit
// Break
// Expression
std::vector<Expression>
// Somme
// Break
LOL;

// std::ostream &operator<<(std::ostream& o, const LOL &l)
// {
//   o << "LOL" << std::endl;
//   return (o);
// }

template <typename Iterator>
class Parser : public boost::spirit::qi::grammar<Iterator
						 // , Program()
						 // , boost::variant<int, std::string>()

						 // , boost::variant<int, Variable>()
						 , LOL()
						 >
{
public:
  Parser() : Parser::base_type(// start_
			       // simple_expression_
			       // list_rvalue_
			       // start_
			       start_
			       , "start")
  {
    using namespace boost::spirit::qi;

    list_index_ = uint_;
    list_ = lit("List ") >> list_index_;

    // works
    new_line_ = lit('\n') | ':';

    digit_ =
      char_("0-9")[_val = _1 - '0'];
    variable_ = char_("A-Z");
    number_ = eps[_val = 0] >> 
      +digit_[_val = (_val * 10 + _1)];

    // should add the *unary soon!
    simple_expression_ = 
      (
       number_
       | numeric_function_
       | (list_ >> '[' >> simple_expression_ >> ']')
       // | (lit('e') >> int_ >> ',' >> char_)
       | variable_
      // | ans_
      // can't remember matrix syntax
      // | (matrix_rvalue_ >> )

      | ('(' >> somme_ >> ')')

      )
      >> eps
      ;

    multiply_ = '*' >> produit_;
    divide_ = '/' >> produit_;
    produit_ = simple_expression_ >> -(multiply_ | divide_);
    add_ = '+' >> somme_;
    substract_ = '-' >> somme_;
    somme_ = produit_ >> -(add_ | substract_);

    numeric_lvalue_ = 
      (list_rvalue_ >> '[' >> // expression_
       simple_expression_
       >> ']')
      | variable_;

    assignment_ = somme_ >> "->" >> numeric_lvalue_;

    expression_ =
      // assignment_
      // | 
      void_expression_
      | 
      somme_
      // | 
      ;

    // start_ %= simple_expression_ >> -lit('\n');

    // uncomment!!!!!! PYRO UNCOMMENT!
    start_ = expression_ % +new_line_;

    // !works

    // should work

    mat_index_ = char_("A-Z") | ans_;

    and_ = lit(" And ");
    ans_ = lit("Ans");

    interrogation_mark_ = '?';



    // !should work

    numeric_function_ = int_function_ | abs_;
    int_function_ = "Int " >> simple_expression_;
    abs_ = "Abs " >> simple_expression_;

    augment_ = "Augment(" >> matrix_rvalue_ >> ',' >> matrix_rvalue_ >> ')';

    axesoff_ = lit("AxesOff");
    axeson_ = lit("AxesOn");
    bg_none_ = lit("BG-None");
    bg_pict_ = lit("BG-Pict ") >> int_;
    break_ = lit("Break") >> attr(Break())
      // >> char_ >> eps
      ;
    circle_ = lit("Circle ") >> simple_expression_ >> ',' >> simple_expression_ >> ',' >> simple_expression_;
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
      >> simple_expression_ >> ','
      >> simple_expression_ >> ','
      >> simple_expression_ >> ','
      >> simple_expression_;
    file_index_ = int_;
    file_ = "File" >> file_index_;
    fix_ = "Fix " >> simple_expression_;
    frac_ = "Frac " >> simple_expression_;
    gconnect_ = "G-Connect";
    gplot_ = "G-Plot";
    gcd_ = "GCD(" >> simple_expression_ >> ',' >> simple_expression_ >> ')';
    getkey_ = "Getkey";

    label_index_ = char_("0-9A-Z");
    goto_ = "Goto " >> label_index_;

    gra_ = "Gra";
    gridoff_ = "GridOff";
    gridon_ = "GridOn";
    horizontal_ = "Horizontal " >> simple_expression_;
    isz_ = "Isz " >> numeric_lvalue_;
    labeloff_ = "LabelOff";
    labelon_ = "LabelOn";


    locate_ = lit("Locate ")
      >> simple_expression_ >> ','
      >> simple_expression_ >> ",\""
      >> *(~char_('"')) >> '"';


    comment_.name("comment_");
    comment_ %= '\'' >> *(char_ - new_line_);
    debug(comment_);

    condition_if_ = lit("If ")
      >> simple_expression_ >> new_line_
      >> lit("Then ")
      >> *(!lit("IfEnd") >> !lit("Else") >> expression_ >> +new_line_)
      >> -(
      	   lit("Else ")
      	   >>
	   +(!lit("IfEnd") >> expression_
	     >> +new_line_)
      	   )
      >> lit("IfEnd")
      ;

    condition_while_ = lit("While ")
      >> simple_expression_ >> new_line_
      >> *(!(lit("WhileEnd")) >> 
    	   (break_ |
    	    expression_)
    	   >> +new_line_)
      >> lit("WhileEnd");

    // condition_do_lpwhile_ = lit("Do") >> new_line_
    // 		>> *(!(lit("LpWhile ")) >> loop_expression_ >> +new_line_)
    // 		>> lit("LpWhile ") >> numeric_rvalue_;

    // condition_for_ = lit("For ") >> numeric_rvalue_ >> simple_arrow_ >> numeric_lvalue_ >> " To "
    // 				 >> numeric_rvalue_ >> " Step " >> numeric_rvalue_ >>  new_line_
    // 		>> *(!(lit("Next")) >> loop_expression_ >> +new_line_)
    // 		>> lit("Next");

    or_ = lit(" Or ");

    
    list_lvalue_ = lit("List") >> -lit(' ') >> list_index_;

    list_const_ = ('{' >> (// numeric_rvalue_
			   simple_expression_
			   % ',') >> '}');
    list_rvalue_ = list_ | list_const_;

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
      ;

  }

private:

  boost::spirit::qi::rule<Iterator
       // , Program()
       // , boost::variant<int, std::string>()

			  , std::vector<Expression>()
			  //boost::variant<int, Variable>()
       > start_;

  // SimpleExpression
  boost::spirit::qi::rule<Iterator, SimpleExpression()> simple_expression_;

  boost::spirit::qi::rule<Iterator// , IntFunction()
			  > numeric_function_;

  boost::spirit::qi::rule<Iterator// , IntFunction()
			  > int_function_;
  boost::spirit::qi::rule<Iterator// , Abs()
			  > abs_;
  boost::spirit::qi::rule<Iterator, Expression()
			  > expression_;

  boost::spirit::qi::rule<Iterator, Somme()> somme_;
  boost::spirit::qi::rule<Iterator, Add()> add_;
  boost::spirit::qi::rule<Iterator, Substract()> substract_;

  boost::spirit::qi::rule<Iterator, Produit()> produit_;
  boost::spirit::qi::rule<Iterator, Multiply()> multiply_;
  boost::spirit::qi::rule<Iterator, Divide()> divide_;

  boost::spirit::qi::rule<Iterator, int()> digit_;
  boost::spirit::qi::rule<Iterator, Variable()> variable_;

  boost::spirit::qi::rule<Iterator> unary_;

  boost::spirit::qi::rule<Iterator> new_line_;

  boost::spirit::qi::rule<Iterator> label_index_;

  boost::spirit::qi::rule<Iterator> assignment_;
  boost::spirit::qi::rule<Iterator, int()> number_;

  boost::spirit::qi::rule<Iterator> double_arrow_;
  boost::spirit::qi::rule<Iterator> simple_arrow_;

  boost::spirit::qi::rule<Iterator, Comment()> comment_;

  boost::spirit::qi::rule<Iterator> locate_;
  boost::spirit::qi::rule<Iterator, If()> condition_if_;
  boost::spirit::qi::rule<Iterator, While()
  			  > condition_while_;
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
  boost::spirit::qi::rule<Iterator
			  , Break()
			  > break_;
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

  boost::spirit::qi::rule<Iterator// , VoidExpression()
			  > void_expression_;
  boost::spirit::qi::rule<Iterator> numeric_lvalue_;
  boost::spirit::qi::rule<Iterator> numeric_rvalue_;
  boost::spirit::qi::rule<Iterator> list_lvalue_;


  boost::spirit::qi::rule<Iterator, ListConst()
			  > list_const_;

  boost::spirit::qi::rule<Iterator, ListRvalue()
			  > list_rvalue_;
  boost::spirit::qi::rule<Iterator> matrix_lvalue_;
  boost::spirit::qi::rule<Iterator> matrix_rvalue_;
  boost::spirit::qi::rule<Iterator> expression_no_comment_;

  boost::spirit::qi::rule<Iterator, unsigned int()> list_index_;
  boost::spirit::qi::rule<Iterator> mat_index_;

  boost::spirit::qi::rule<Iterator, List()
			  > list_;
  boost::spirit::qi::rule<Iterator> matrix_;
};

#endif	// !PARSER_HPP_
