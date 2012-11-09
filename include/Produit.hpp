#ifndef PRODUIT_HPP_
# define PRODUIT_HPP_

# include <iosfwd>
# include <boost/fusion/include/adapt_struct.hpp>
# include <vector>

# include "SimpleExpression.hpp"

struct Produit
{
  typedef std::vector<SimpleExpression> TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(Produit,
			  (Produit::TypeValue, value)
			  )

std::ostream &operator<<(std::ostream &o, const Produit &v);

#endif	// !PRODUIT_HPP_
