
#ifndef COMMENT_HPP_
# define COMMENT_HPP_

# include <string>
# include <boost/fusion/include/adapt_struct.hpp>

struct Comment
{
  std::string str_;
};

BOOST_FUSION_ADAPT_STRUCT(
			  Comment,
			  (std::string, str_)
			  )

#endif	// !COMMENT_HPP_
