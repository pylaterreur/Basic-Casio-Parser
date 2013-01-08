#ifndef RUN_HPP_
# define RUN_HPP_

# include <vector>
# include "Expression.hpp"
# include "Comment.hpp"

void run(const std::vector<boost::variant<Expression, Comment> >& program);

#endif	// !RUN_HPP_
