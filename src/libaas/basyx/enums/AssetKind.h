#ifndef BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H
#define BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {

enum class AssetKind {
    Type,
    Instance,
    NotApplicable,
};

class AssetKind_
{
public:
    using type_t = AssetKind;
public:
    static AssetKind from_string(util::string_view str_v);
    static const char * to_string(AssetKind value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H */
