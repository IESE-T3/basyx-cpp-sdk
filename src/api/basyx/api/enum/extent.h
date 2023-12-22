#ifndef BASYX_SUBMODEL_ENUMERATIONS_EXTENT_H
#define BASYX_SUBMODEL_ENUMERATIONS_EXTENT_H

#include <string>

namespace basyx {
namespace api {

enum class Extent {
    WithoutBLOBValue,
    WithBLOBValue,
};

class Extent_
{
public:
    static Extent from_string(const std::string & name);
    static const char * to_string(Extent value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_EXTENT_H */
