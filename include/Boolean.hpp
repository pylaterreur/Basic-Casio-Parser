#ifndef BOOLEAN_HPP_
# define BOOLEAN_HPP_

# include <boost/fusion/include/adapt_struct.hpp>

# include "Somme.hpp"

struct NotEqual;
struct Equal;
struct Greater;
struct Smaller;
struct GreaterEqual;
struct SmallerEqual;
struct And;
struct Or;

struct Boolean
{
  Somme left;
  typedef boost::optional<boost::variant<
			    boost::recursive_wrapper<NotEqual>,
			    boost::recursive_wrapper<Equal>,
			    boost::recursive_wrapper<Greater>,
			    boost::recursive_wrapper<Smaller>,
			    boost::recursive_wrapper<GreaterEqual>,
			    boost::recursive_wrapper<SmallerEqual>,
			    boost::recursive_wrapper<And>,
			    boost::recursive_wrapper<Or>
			    >
  > RightType;
  RightType right;
};

BOOST_FUSION_ADAPT_STRUCT(Boolean,
			  (Somme, left)
			  (Boolean::RightType, right)
			  )

struct NotEqual
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(NotEqual,
			  (Boolean, right)
			  )

struct Equal
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(Equal,
			  (Boolean, right)
			  )

struct Greater
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(Greater,
			  (Boolean, right)
			  )

struct Smaller
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(Smaller,
			  (Boolean, right)
			  )

struct GreaterEqual
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(GreaterEqual,
			  (Boolean, right)
			  )

struct SmallerEqual
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(SmallerEqual,
			  (Boolean, right)
			  )

struct And
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(And,
			  (Boolean, right)
			  )

struct Or
{
  Boolean right;
};

BOOST_FUSION_ADAPT_STRUCT(Or,
			  (Boolean, right)
			  )

#endif	// !BOOLEAN_HPP_
