
#ifndef LOCATE_HPP_
# define LOCATE_HPP_

# include <string>
# include <boost/spirit/include/qi.hpp>
# include <boost/tuple/tuple.hpp>
# include "Parser.hpp"

template <typename Iterator>
class Locate;

template <typename Iterator>
struct AttributeType<Locate<Iterator> >
{
  typedef boost::tuple<int, int, std::string> attribute_type;
};

template <typename Iterator>
class Locate : public AttributeType<Locate<Iterator> >,
	       public boost::spirit::qi::grammar<Iterator,
						 typename AttributeType<Locate<Iterator> >::attribute_type()>
{
public:
  using typename AttributeType<Locate<Iterator> >::attribute_type;

  Locate() : Locate::base_type(start_, "locate")
  {
    start_ %= (boost::spirit::qi::lit("Locate ")
	       >> boost::spirit::qi::int_ >> ','
	       >> boost::spirit::qi::int_ >> ",\""
	       >> *(~boost::spirit::qi::char_('"')) >> '"');
  }

private:
  boost::spirit::qi::rule<Iterator, attribute_type()> start_;
};

#endif	// !LOCATE_HPP_
