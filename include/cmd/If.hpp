
#ifndef IF_HPP_
# define IF_HPP_

# include "Expression.hpp"

struct If
{
  // condition
  NumericRvalue test;

  std::vector<Expression> if_;
  std::vector<Expression> else_;  
};

#endif	// !IF_HPP_
