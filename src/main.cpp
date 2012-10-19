
#include <iostream>

#include "Parser.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Usage: " << *argv << "prog [subprog ...]" << std::endl;
      return (-1);
    }
  Parser<std::string::const_iterator> p;

  // Program
  // int
  boost::variant<int, std::string>
    program;

  const std::string str(argv[1]);

  auto begin = str.begin();
  auto end = str.end();

  bool r = boost::spirit::qi::parse(begin, end, p, program);

  if (r && begin == end)
    {
      std::cout << "program " << program << std::endl;
    }
  else
    {
      std::cerr << "fail" << std::endl;
    }
  std::cout << "Done" << std::endl;
}
