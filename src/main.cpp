
#include <iostream>
#include <ios>
#include <fstream>
#include <iterator>

#include "Parser.hpp"
#include "Run.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << *argv << "filename" << std::endl;
      return (-1);
    }

  typedef std::string::const_iterator toto;

  Parser<toto> p;

  // Program
  // int
  // boost::variant<int, Variable>
  // SimpleExpression
  // List
  // ListRvalue

  LOL
    program;

  //  const std::string str(argv[1]);
  std::ifstream in(argv[1]);
  if (!in.good())
    {
      std::cerr << "Opening file \"" << argv[1] << "\" failed" << std::endl;
      return (-1);
    }

  std::stringstream buffer;

  buffer << in.rdbuf();
  const std::string str(buffer.str());

  auto begin = str.begin();
  auto end = str.end();

  bool r = boost::spirit::qi::parse(begin, end, p, program
				    );

  if (r && begin == end)
    {
      std::cout << "program " // << program
		<< std::endl;
    }
  else
    {
      std::string str(begin, end);
      std::cerr << "fail at \""
		<< str << "\""
		<< std::endl;
    }
  std::cout << "Done" << std::endl;
  run(program);
}
