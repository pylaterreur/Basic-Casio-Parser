#ifndef VARIABLE_HPP_
# define VARIABLE_HPP_

# include <iosfwd>
# include <boost/fusion/include/adapt_struct.hpp>

struct Variable
{
  typedef char TypeName;
  TypeName name;
};

BOOST_FUSION_ADAPT_STRUCT(Variable,
			  (Variable::TypeName, name)
			  )

std::ostream &operator<<(std::ostream &o, const Variable &v);

#endif	// !VARIABLE_HPP_
