#ifndef GOTO_HPP_
# define GOTO_HPP_

# include <boost/fusion/include/adapt_struct.hpp>

typedef char LabelIndex;

struct Goto
{
  LabelIndex value;
};

BOOST_FUSION_ADAPT_STRUCT(Goto,
			  (LabelIndex, value)
			  )

#endif	// !GOTO_HPP_
