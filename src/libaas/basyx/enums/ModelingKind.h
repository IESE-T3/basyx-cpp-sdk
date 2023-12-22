#ifndef BASYX_SUBMODEL_ENUMERATIONS_MODELINGKIND_H
#define BASYX_SUBMODEL_ENUMERATIONS_MODELINGKIND_H

#include <string>

namespace basyx {

enum class ModelingKind {
    Template,
    Instance,
    None,
};

class ModelingKind_
{
public:
    using type_t = ModelingKind;
public:
    static ModelingKind from_string(const std::string & name);
    static const char * to_string(ModelingKind value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_MODELINGKIND_H */
