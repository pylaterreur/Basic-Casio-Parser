#ifndef PRODUIT_HPP_
# define PRODUIT_HPP_

# include <iosfwd>
# include <boost/fusion/include/adapt_struct.hpp>
# include <vector>

# include <boost/spirit/include/qi_optional.hpp>

# include "SimpleExpression.hpp"

struct Multiply;
struct Divide;

struct Produit
{
  SimpleExpression left;
  typedef boost::optional<boost::variant<boost::recursive_wrapper<Multiply>,
					 boost::recursive_wrapper<Divide> > > RightType;
  RightType right;
};

BOOST_FUSION_ADAPT_STRUCT(Produit,
			  (SimpleExpression, left)
			  (Produit::RightType, right)
			  )

struct Multiply
{
  Produit value;
};

BOOST_FUSION_ADAPT_STRUCT(Multiply,
			  (Produit, value)
			  )

struct Divide
{
  Produit value;
};

BOOST_FUSION_ADAPT_STRUCT(Divide,
			  (Produit, value)
			  )

std::ostream &operator<<(std::ostream &o, const Produit &v);

#endif	// !PRODUIT_HPP_
