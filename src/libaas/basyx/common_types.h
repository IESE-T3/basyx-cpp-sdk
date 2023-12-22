#ifndef BASYX_METAMODEL_COMMON_TYPES_H
#define BASYX_METAMODEL_COMMON_TYPES_H

#include <basyx/util/constrained_string/constrained_string.hpp>

namespace basyx
{
	using LabelType = util::constrained_string<1, 64>;
	using Identifier = util::constrained_string<1, 2000>;
	using ContentType = util::constrained_string<1, 100>;
	using PathType = util::constrained_string<1, 2000>;

};

#endif // BASYX_METAMODEL_COMMON_TYPES_H
