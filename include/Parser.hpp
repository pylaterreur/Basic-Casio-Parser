
#ifndef PARSER_HPP_
# define PARSER_HPP_

# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix.hpp>
# include <boost/variant.hpp>

# include "Expression.hpp"

# include "Comment.hpp"
# include "Variable.hpp"
# include "List.hpp"
# include "Matrix.hpp"
# include "SimpleExpression.hpp"
# include "Produit.hpp"
# include "Somme.hpp"

# include "functions/Cross.hpp"
# include "functions/Dot.hpp"

# include "While.hpp"

# include "Break.hpp"

# include "NumericLvalue.hpp"

typedef
// SimpleExpression
// List
// ListRvalue
// Produit
// Break
// Expression
std::vector<boost::variant<Expression, Comment> >
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
  // struct Option
  // {};
  // struct Breakable
  // {};
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

    matrix_index_ = char_("A-Z") // | ans_
      ;
    matrix_ = lit("Mat ") >> matrix_index_;
    matrix_helper_index_ = matrix_ >> '[' >> simple_expression_ >> "][" >> simple_expression_  >> ']';

    // works
    new_line_ = lit('\n') | ':';

    digit_ =
      char_("0-9")[_val = _1 - '0'];
    variable_ = char_("A-Z");
    number_ = eps[_val = 0] >> 
      +digit_[_val = (_val * 10 + _1)];

    list_helper_index_ = list_ >> '[' >> simple_expression_ >> ']';

    // should add the *unary soon!
    simple_expression_ = 
      (
       number_
       | numeric_function_
       | list_helper_index_
       | matrix_helper_index_

       // | (lit('e') >> int_ >> ',' >> char_)
       | variable_
      // | ans_
      // can't remember matrix syntax
      // | (matrix_rvalue_ >> )

      | ('(' >> boolean_ >> ')')

      )
      >> eps
      ;

    multiply_ = '*' >> produit_;
    divide_ = '/' >> produit_;
    produit_ = simple_expression_ >> -(multiply_ | divide_);
    add_ = '+' >> somme_;
    substract_ = '-' >> somme_;
    somme_ = produit_ >> -(add_ | substract_);

      not_equal_ = "!=" >> boolean_;
      equal_ = "=" >> boolean_;
      greater_ = ">" >> boolean_;
      smaller_ = "<" >> boolean_;
      greater_equal_ = ">=" >> boolean_;
      smaller_equal_ = "<=" >> boolean_;
      and_ = " And " >> boolean_;
      or_ = " Or " >> boolean_;
      boolean_ = somme_ >> -(not_equal_ | equal_ | greater_ | smaller_ | greater_equal_ | smaller_equal_
			     | and_
			     | or_
			     );

    numeric_lvalue_ = 
      list_helper_index_
      | matrix_helper_index_
      | variable_
      // | dim_list_
      ;

    numeric_assignment_ = boolean_ >> "->" >> numeric_lvalue_;

    list_assignment_ = list_rvalue_ >> "->" >> (list_ // | dim_matrix_
						)
      ;

    matrix_assignment_ = matrix_rvalue_ >> "->" >> matrix_;

    matrix_function_ = augment_ >> eps;

    matrix_rvalue_ =
      matrix_function_
      | matrix_
      | matrix_const_;

    assignment_ = numeric_assignment_
      | list_assignment_
      | matrix_assignment_
      ;

    expression_ =
      // assignment_
      // | 
      void_expression_(_r1, _r2)
      | matrix_rvalue_
      | 
      boolean_
      | interrogation_mark_
      // | list_rvalue_
      // | 
      ;

    // start_ %= simple_expression_ >> -lit('\n');

    // uncomment!!!!!! PYRO UNCOMMENT!
    start_ = (expression_(false, true) | comment_) % +new_line_;

    // !works

    // should work

    ans_ = lit("Ans") >> attr(Ans());

    interrogation_mark_ = "?->" >> numeric_lvalue_;


    // !should work

    numeric_function_ = int_function_ | abs_ | getkey_;
    int_function_ = "Int " >> simple_expression_;
    abs_ = "Abs " >> simple_expression_;

    augment_ = "Augment(" >> matrix_rvalue_ >> ',' >> matrix_rvalue_ >> ')';

    axeson_ = lit("AxesOn") >> attr(AxesOn());
    axesoff_ = lit("AxesOff") >> attr(AxesOff());
    bg_none_ = lit("BG-None") >> attr(BgNone());
    bg_pict_ = lit("BG-Pict ") >> int_;
    break_ = lit("Break") >> attr(Break());
    circle_ = lit("Circle ") >> simple_expression_ >> ',' >> simple_expression_ >> ',' >> simple_expression_;
    clrgraph_ = lit("ClrGraph") >> attr(ClrGraph());
    clrlist_ = lit("ClrList ") >> -(list_index_);
    clrmat_ = lit("ClrMat") >> -(matrix_index_);
    clrtext_ = lit("ClrText") >> attr(ClrText());
    cls_ = lit("Cls") >> attr(Cls());
    coordoff_ = lit("CoordOff") >> attr(CoordOff());
    coordon_ = lit("CoordOn") >> attr(CoordOn());
    cross_ = lit("Cross") >> attr(Cross());
    deg_ = "Deg" >> attr(Deg());
    derivoff_ = "DerivOff" >> attr(DerivOff());
    derivon_ = "DerivOn" >> attr(DerivOn());
    dim_matrix_ = "Dim " >> matrix_lvalue_;
    dim_list_ = "Dim " >> list_;
    dot_ = "Dot" >> attr(Dot());
    drawdyna_ = "DrawDyna" >> attr(DrawDyna());
    drawgraph_ = "DrawGraph" >> attr(DrawGraph());
    drawoff_ = "DrawOff" >> attr(DrawOff());
    drawon_ = "DrawOn" >> attr(DrawOn());
    drawstat_ = "DrawStat" >> attr(DrawStat());
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
    getkey_ = "Getkey" >> attr(GetKey());

    label_index_ = char_("0-9A-Z");
    goto_ = "Goto " >> label_index_;

    gra_ = "Gra" >> attr(Gra());
    gridoff_ = "GridOff" >> attr(GridOff());
    gridon_ = "GridOn" >> attr(GridOn());
    horizontal_ = "Horizontal " >> simple_expression_;
    isz_ = "Isz " >> numeric_lvalue_;
    labeloff_ = "LabelOff" >> attr(LabelOff());
    labelon_ = "LabelOn" >> attr(LabelOn());

    string_ = '"' >> *(~char_('"')) >> '"';

    locate_ = lit("Locate ")
      >> simple_expression_ >> ','
      >> simple_expression_ >> ","
      >> string_;


    comment_ %= '\'' >> *(char_ - new_line_);

    condition_if_ = lit("If ")
      >> simple_expression_ >> new_line_
      >> lit("Then ")
      >> *(!lit("IfEnd") >> !lit("Else") >> expression_(_r1, true) >> +new_line_)
      >> -(
      	   lit("Else ")
      	   >>
	   +(!lit("IfEnd") >> expression_(_r1, true)
	     >> +new_line_)
      	   )
      >> lit("IfEnd")
      ;

    condition_while_ = lit("While ")
      >> simple_expression_ >> new_line_
      >> *(!(lit("WhileEnd")) >> 
    	   (expression_(true, true))
    	   >> +new_line_)
      >> lit("WhileEnd");

    condition_do_lpwhile_ = lit("Do") >> new_line_
				      >> *(!(lit("LpWhile ")) >> expression_(true, true) >> +new_line_)
				      >> lit("LpWhile ") >> simple_expression_;

    condition_for_ = lit("For ")
      >> numeric_assignment_ >> " To "
      >> simple_expression_ >> " Step " >> simple_expression_ >>  new_line_
      >> *(!(lit("Next")) >> expression_(true, true) >> +new_line_)
      >> lit("Next");

    list_const_ = ('{' >> (// numeric_rvalue_
			   simple_expression_
			   % ',') >> '}');

    matrix_const_ = '[' >> +('[' >> (// numeric_rvalue_
				     simple_expression_
				     % ',') >> ']') >> ']';

    list_rvalue_ = list_ | list_const_;

    double_arrow_ = simple_expression_ >> lit("=>") >> expression_(_r1, false);

    void_expression_ =
      locate_
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
      | (eps[_pass = (_r2 == true)] >> (condition_if_(_r1)
					| double_arrow_(_r1)
					| condition_while_
					| condition_do_lpwhile_
					| condition_for_ )
	 )
      | assignment_
      //      03:07 < VeXocide> pystache, eps[_pass = <phoenix expression using qi::_r1>] >> <some parser>
      | (eps[_pass = (_r1 == true)] >> break_)
      // | 
      ;

  }

private:

  boost::spirit::qi::rule<Iterator, std::vector<boost::variant<Expression, Comment> >()> start_;
  boost::spirit::qi::rule<Iterator, Expression(bool breakable, bool complex)> expression_;
  boost::spirit::qi::rule<Iterator, SimpleExpression()> simple_expression_;
  boost::spirit::qi::rule<Iterator, Somme()> somme_;
  boost::spirit::qi::rule<Iterator, Add> add_;
  boost::spirit::qi::rule<Iterator, Substract()> substract_;
  boost::spirit::qi::rule<Iterator, Produit()> produit_;
  boost::spirit::qi::rule<Iterator, Multiply()> multiply_;
  boost::spirit::qi::rule<Iterator, Divide()> divide_;
  boost::spirit::qi::rule<Iterator, int()> number_;
  boost::spirit::qi::rule<Iterator, int()> digit_;
  boost::spirit::qi::rule<Iterator, Variable()> variable_;
  boost::spirit::qi::rule<Iterator, NumericFunction()> numeric_function_;
  boost::spirit::qi::rule<Iterator, Int()> int_function_;
  boost::spirit::qi::rule<Iterator, Abs()> abs_;
  boost::spirit::qi::rule<Iterator> new_line_;
  boost::spirit::qi::rule<Iterator, char()> label_index_;
  boost::spirit::qi::rule<Iterator, Comment()> comment_;
  boost::spirit::qi::rule<Iterator, If(bool breakable)> condition_if_;
  boost::spirit::qi::rule<Iterator, While()> condition_while_;
  boost::spirit::qi::rule<Iterator, Break()> break_;
  boost::spirit::qi::rule<Iterator, AxesOff()> axesoff_;
  boost::spirit::qi::rule<Iterator, AxesOn()> axeson_;
  boost::spirit::qi::rule<Iterator, BgNone()> bg_none_;
  boost::spirit::qi::rule<Iterator, LabelOn()> labelon_;
  boost::spirit::qi::rule<Iterator, LabelOff()> labeloff_;
  boost::spirit::qi::rule<Iterator, ClrGraph()> clrgraph_;
  boost::spirit::qi::rule<Iterator, ClrText()> clrtext_;
  boost::spirit::qi::rule<Iterator, Cls()> cls_;
  boost::spirit::qi::rule<Iterator, CoordOff()> coordoff_;
  boost::spirit::qi::rule<Iterator, CoordOn()> coordon_;
  boost::spirit::qi::rule<Iterator, Cross()> cross_;
  boost::spirit::qi::rule<Iterator, Deg()> deg_;
  boost::spirit::qi::rule<Iterator, DerivOn()> derivon_;
  boost::spirit::qi::rule<Iterator, DerivOff()> derivoff_;
  boost::spirit::qi::rule<Iterator, GetKey()> getkey_;
  boost::spirit::qi::rule<Iterator, Circle()> circle_;
  boost::spirit::qi::rule<Iterator, DrawStat()> drawstat_;
  boost::spirit::qi::rule<Iterator, DrawDyna()> drawdyna_;
  boost::spirit::qi::rule<Iterator, DrawGraph()> drawgraph_;
  boost::spirit::qi::rule<Iterator, DrawOff()> drawoff_;
  boost::spirit::qi::rule<Iterator, DrawOn()> drawon_;
  boost::spirit::qi::rule<Iterator, std::string()> string_;
  boost::spirit::qi::rule<Iterator, Locate()> locate_;
  boost::spirit::qi::rule<Iterator, GridOff()> gridoff_;
  boost::spirit::qi::rule<Iterator, GridOn()> gridon_;
  boost::spirit::qi::rule<Iterator, FLine()> fline_;
  boost::spirit::qi::rule<Iterator, Dsz()> dsz_;
  boost::spirit::qi::rule<Iterator, Isz()> isz_;
  boost::spirit::qi::rule<Iterator, NumericLvalue()> numeric_lvalue_;
  boost::spirit::qi::rule<Iterator, Assignment()> assignment_;
  boost::spirit::qi::rule<Iterator, NumericAssignment()> numeric_assignment_;

  boost::spirit::qi::rule<Iterator, ListConst()> list_const_;
  boost::spirit::qi::rule<Iterator, ListRvalue()> list_rvalue_;
  boost::spirit::qi::rule<Iterator, ListAssignment()> list_assignment_;
  boost::spirit::qi::rule<Iterator, unsigned int()> list_index_;
  boost::spirit::qi::rule<Iterator, ListIndex()> list_helper_index_;
  boost::spirit::qi::rule<Iterator, List()> list_;

  boost::spirit::qi::rule<Iterator, MatrixConst()> matrix_const_;
  boost::spirit::qi::rule<Iterator, MatrixRvalue()> matrix_rvalue_;
  boost::spirit::qi::rule<Iterator, MatrixAssignment()> matrix_assignment_;
  boost::spirit::qi::rule<Iterator, char()> matrix_index_;
  boost::spirit::qi::rule<Iterator, MatrixIndex()> matrix_helper_index_;
  boost::spirit::qi::rule<Iterator, Matrix()> matrix_;
  boost::spirit::qi::rule<Iterator, MatrixFunction()> matrix_function_;

  boost::spirit::qi::rule<Iterator, For()> condition_for_;
  boost::spirit::qi::rule<Iterator, Gra()> gra_;
  boost::spirit::qi::rule<Iterator, DoubleArrow(bool breakable)> double_arrow_;
  boost::spirit::qi::rule<Iterator, VoidExpression(bool breakable, bool complex)> void_expression_;
  boost::spirit::qi::rule<Iterator, InterrogationMark()> interrogation_mark_;
  boost::spirit::qi::rule<Iterator, LpWhile()> condition_do_lpwhile_;
  boost::spirit::qi::rule<Iterator, Boolean()> boolean_;
  boost::spirit::qi::rule<Iterator, And()> and_;
  boost::spirit::qi::rule<Iterator, Or()> or_;
  boost::spirit::qi::rule<Iterator> not_;
  boost::spirit::qi::rule<Iterator, Greater()> greater_;
  boost::spirit::qi::rule<Iterator, Smaller()> smaller_;
  boost::spirit::qi::rule<Iterator, Equal()> equal_;
  boost::spirit::qi::rule<Iterator, NotEqual()> not_equal_;
  boost::spirit::qi::rule<Iterator, GreaterEqual()> greater_equal_;
  boost::spirit::qi::rule<Iterator, SmallerEqual()> smaller_equal_;
  boost::spirit::qi::rule<Iterator, Horizontal()> horizontal_;
  boost::spirit::qi::rule<Iterator, Ans()> ans_;
  boost::spirit::qi::rule<Iterator, Gcd()> gcd_;
  boost::spirit::qi::rule<Iterator, Dot()> dot_;
  boost::spirit::qi::rule<Iterator, Frac()> frac_;

  boost::spirit::qi::rule<Iterator, Augment()> augment_;
  boost::spirit::qi::rule<Iterator> bg_pict_;
  boost::spirit::qi::rule<Iterator> clrlist_;
  boost::spirit::qi::rule<Iterator> clrmat_;
  boost::spirit::qi::rule<Iterator> dim_matrix_;
  boost::spirit::qi::rule<Iterator// , DimList()
			  > dim_list_;
  boost::spirit::qi::rule<Iterator> file_;
  boost::spirit::qi::rule<Iterator> fix_;
  boost::spirit::qi::rule<Iterator> gconnect_;
  boost::spirit::qi::rule<Iterator> gplot_;
  boost::spirit::qi::rule<Iterator> goto_;

  // not done yet
  boost::spirit::qi::rule<Iterator> lbl_;
  boost::spirit::qi::rule<Iterator> lcm_;
  boost::spirit::qi::rule<Iterator> line_;
  boost::spirit::qi::rule<Iterator> list_mat_;
  boost::spirit::qi::rule<Iterator> max_;

  // end not done yet

  boost::spirit::qi::rule<Iterator> file_index_;

  boost::spirit::qi::rule<Iterator> matrix_lvalue_;
};

#endif	// !PARSER_HPP_
