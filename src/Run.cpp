
#include <iostream>

#include <boost/variant.hpp>

#include "Run.hpp"

namespace
{
  class Run : public boost::static_visitor<>
  {
  public:
    template <typename T>
    void operator()(const T&) const
    {
      std::cout << "Default visitor : " << typeid(T).name() << std::endl;
    }

    void operator()(const Comment &) const
    {}

    void operator()(const Expression &expr) const
    {
      std::cout << "Expression visitor" << std::endl;
      boost::apply_visitor(*this, expr.value);
    }

    void operator()(const VoidExpression &expr) const
    {
      std::cout << "VoidExpression visitor" << std::endl;
      boost::apply_visitor(*this, expr.value);
    }

  };
}

void run(const std::vector<boost::variant<Expression, Comment> >& program)
{
  std::cout << "LOL" << std::endl;
  for (const auto &i : program)
    {
      // Goto's won't work for the moment
      boost::apply_visitor(Run(), i);
      //      break;
    }
}
