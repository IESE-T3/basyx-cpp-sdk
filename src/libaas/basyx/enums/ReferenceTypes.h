#ifndef REFERENCE_TYPES_H
#define REFERENCE_TYPES_H

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {

enum class ReferenceTypes {
   ExternalReference,
   ModelReference,
};

class ReferenceTypes_
{
public:
    using type_t = ReferenceTypes;
public:
    static ReferenceTypes from_string(util::string_view name);
    static const char * to_string(ReferenceTypes value);
};


}

#endif // REFERENCE_TYPES_H
