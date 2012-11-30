#ifndef CLRLIST_HPP_
# define CLRLIST_HPP_

# include <boost/optional.hpp>
# include <boost/fusion/include/adapt_struct.hpp>

# include "List.hpp"

struct ClrList
{
  typedef boost::optional<List::TypeName> Type;
  Type value;
};

BOOST_FUSION_ADAPT_STRUCT(ClrList,
			  (ClrList::Type, value)
			  )

#endif	// CLRLIST_HPP_
