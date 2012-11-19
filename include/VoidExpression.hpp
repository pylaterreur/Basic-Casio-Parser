
#ifndef VOIDEXPRESSION_HPP_
# define VOIDEXPRESSION_HPP_

# include <iosfwd>

# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/variant.hpp>

# include "If.hpp"
# include "While.hpp"

# include "functions/AxesOff.hpp"
# include "functions/AxesOn.hpp"
# include "functions/BgNone.hpp"
# include "functions/ClrGraph.hpp"
# include "functions/ClrText.hpp"
# include "functions/Cls.hpp"
# include "functions/CoordOff.hpp"
# include "functions/CoordOn.hpp"
# include "functions/Cross.hpp"
# include "functions/Deg.hpp"
# include "functions/DerivOff.hpp"
# include "functions/DerivOn.hpp"
# include "functions/GridOff.hpp"
# include "functions/GridOn.hpp"
# include "functions/LabelOff.hpp"
# include "functions/LabelOn.hpp"
# include "functions/Circle.hpp"
# include "functions/DrawStat.hpp"
# include "functions/DrawDyna.hpp"
# include "functions/DrawGraph.hpp"
# include "functions/DrawOn.hpp"
# include "functions/DrawOff.hpp"
# include "functions/Locate.hpp"
# include "functions/FLine.hpp"
# include "functions/Isz.hpp"
# include "functions/Dsz.hpp"

# include "Assignment.hpp"

struct VoidExpression
{
  typedef boost::variant<If, While,
			 AxesOff,
			 AxesOn,
			 BgNone,
			 ClrGraph,
			 ClrText,
			 Cls,
			 CoordOff,
			 CoordOn,
			 Deg,
			 DerivOff,
			 DerivOn,
			 GridOff,
			 GridOn,
			 LabelOff,
			 LabelOn,
			 Circle,
			 Locate,
			 FLine,
			 Isz,
			 Dsz
			 , Assignment
			 > TypeValue;
  TypeValue value;
};

BOOST_FUSION_ADAPT_STRUCT(VoidExpression,
			  (VoidExpression::TypeValue, value)
			  )

std::ostream &operator<<(std::ostream& o, const VoidExpression&);

#endif	// !VOIDEXPRESSION_HPP_
