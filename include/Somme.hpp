#ifndef SOMME_HPP_
# define SOMME_HPP_

# include <iosfwd>
# include <boost/fusion/include/adapt_struct.hpp>
# include <vector>

# include <boost/spirit/include/qi_optional.hpp>

# include "Produit.hpp"

struct Add;
struct Substract;

struct Somme
{
  Produit left;
  typedef boost::optional<boost::variant<boost::recursive_wrapper<Add>,
					 boost::recursive_wrapper<Substract> > > RightType;
  RightType right;
};

BOOST_FUSION_ADAPT_STRUCT(Somme,
			  (Produit, left)
			  (Somme::RightType, right)
			  )

struct Add
{
  Somme value;
};

BOOST_FUSION_ADAPT_STRUCT(Add,
			  (Somme, value)
			  )

struct Substract
{
  Somme value;
};

BOOST_FUSION_ADAPT_STRUCT(Substract,
			  (Somme, value)
			  )

std::ostream &operator<<(std::ostream &o, const Somme &v);

#endif	// !SOMME_HPP_
