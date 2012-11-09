#ifndef INTFUNCTION_HPP_
# define INTFUNCTION_HPP_

# include <iosfwd>
# include <boost/fusion/include/adapt_struct.hpp>

struct IntFunction
{
  TypeName name;
};

BOOST_FUSION_ADAPT_STRUCT(IntFunction,
			  (IntFunction::TypeName, name)
			  )

std::ostream &operator<<(std::ostream &o, const IntFunction &v);

#endif	// !INTFUNCTION_HPP_
